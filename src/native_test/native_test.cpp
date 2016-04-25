#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <include/libplatform/libplatform.h>
#include <include/v8.h>

#include "./array_buff_alloc.h"
#include "./util_methods.h"
#include "./option_parser.h"
#include "./global_funcs.h"

using namespace v8;
using namespace std;


// methods for initing and destroying v8
Platform* init(int argc, char* argv[]);
void deinit(Platform *&platform);

// methods
Isolate* create_isolate();
Local<Context> create_context(Isolate *isolate);
MaybeLocal<String> to_v8_string(Isolate *isolate, char *c_str, int length);
void ReportException(Isolate* isolate, TryCatch* try_catch);
bool ExecuteString(Isolate* isolate, Local<String> source, Local<Value> name, bool print_result, bool report_exceptions);

int main(int argc, char* argv[]) {
	// init v8 and create platform
	Platform *platform = init(argc, argv);
	
	// create isolate
	Isolate* isolate = create_isolate();

    // check for options
    if (argc > 1) {
        // read options
        option_parser parser(argc, argv);

        if (parser.error()) {
            return 1;
        }

        // read script
        int length;
        char *script_source = UtilMethods::fileToBuffer(parser.script(), length);

        // if error openning file, exit
        if (script_source == NULL) {
            fprintf(stderr, "error openning script \"%s\"", argv[1]);
            return 1;
        }

        // verbose detail
        if (parser.verbose()) {
            printf("...Openning script \"%s\"\n", parser.script());
        }

        // exec script
        int result;
        {
            Isolate::Scope isolate_scope(isolate);
            HandleScope handle_scope(isolate);

            // create context
            Local<Context> context = create_context(isolate);

            // check of error
            if (context.IsEmpty()) {
                fprintf(stderr, "error creating context\n");
                return 1;
            }

            v8::Context::Scope context_scope(context);

            // convert to v8 string
            Local<String> string_source;
            if (to_v8_string(isolate, script_source, length).ToLocal(&string_source)) {
                // execute script
                Local<String> script_name = String::NewFromUtf8(isolate, parser.script());
                bool success = ExecuteString(isolate, string_source, script_name, false, true);

                while (platform::PumpMessageLoop(platform, isolate))
                    continue;

                if (!success) {
                    return 1;
                }
            }
        }
    } else {
        fprintf(stderr, "script path not given\n");
        return 1;
    }

	// delete platform and turn down v8
    isolate->Dispose();
	deinit(platform);
	return 0;
}

Platform* init(int argc, char* argv[]) {
	// Initialize V8.
    V8::InitializeICU();
    V8::InitializeExternalStartupData(argv[0]);

    // create platform
    Platform* platform = platform::CreateDefaultPlatform();
    V8::InitializePlatform(platform);
    V8::Initialize();
    V8::SetFlagsFromCommandLine(&argc, argv, true);

    return platform;
}

void deinit(Platform *&platform) {
	V8::Dispose();
    V8::ShutdownPlatform();
    delete platform;
}

Isolate* create_isolate() {
	ArrayBufferAllocator* array_buffer_allocator = new ArrayBufferAllocator;
	Isolate::CreateParams create_params;
	create_params.array_buffer_allocator = array_buffer_allocator;
	return Isolate::New(create_params);
}

Local<Context> create_context(Isolate *isolate) {
    Local<ObjectTemplate> global = ObjectTemplate::New(isolate);

    // add print function
    Local<String> func_name = String::NewFromUtf8(isolate, "print", NewStringType::kNormal)
            .ToLocalChecked();
    Local<FunctionTemplate> print_tmpl = FunctionTemplate::New(isolate, Print);

    // set global methods
    global->Set(isolate, "print", FunctionTemplate::New(isolate, Print));
    global->Set(isolate, "printl", FunctionTemplate::New(isolate, PrintL));
    global->Set(isolate, "printf", FunctionTemplate::New(isolate, PrintFormat));
    return Context::New(isolate, NULL, global);
}

MaybeLocal<String> to_v8_string(Isolate *isolate, char *c_str, int length) {
    if (c_str == NULL) {
        return MaybeLocal<String>();
    }

    // return string
    return String::NewFromUtf8(isolate, c_str, NewStringType::kNormal, static_cast<int>(length));
}

bool ExecuteString(Isolate* isolate, Local<String> source, Local<Value> name, bool print_result, bool report_exceptions) {
    TryCatch try_catch(isolate);
    ScriptOrigin origin(name);
    Local<Context> context(isolate->GetCurrentContext());
    Local<Script> script;
    if (!Script::Compile(context, source, &origin).ToLocal(&script)) {
        // Print errors that happened during compilation.
        if (report_exceptions) {
            ReportException(isolate, &try_catch);
        }
        return false;
    } else {
        Local<Value> result;
        if (!script->Run(context).ToLocal(&result)) {
            assert(try_catch.HasCaught());
            // Print errors that happened during execution.
            if (report_exceptions)
                ReportException(isolate, &try_catch);
            return false;
        } else {
            assert(!try_catch.HasCaught());
            if (print_result && !result->IsUndefined()) {
                // If all went well and the result wasn't undefined then print
                // the returned value.
                String::Utf8Value str(result);
                const char* cstr = UtilMethods::ToCString(str);
                printf("%s\n", cstr);
            }
            return true;
        }
    }
}

void ReportException(Isolate* isolate, TryCatch* try_catch) {
    HandleScope handle_scope(isolate);
    String::Utf8Value exception(try_catch->Exception());
    const char* exception_string = UtilMethods::ToCString(exception);
    Local<Message> message = try_catch->Message();
    if (message.IsEmpty()) {
        // V8 didn't provide any extra information about this error; just
        // print the exception.
        fprintf(stderr, "%s\n", exception_string);
    } else {
        // Print (filename):(line number): (message).
        String::Utf8Value filename(message->GetScriptOrigin().ResourceName());
        Local<Context> context(isolate->GetCurrentContext());
        const char* filename_string = UtilMethods::ToCString(filename);
        int linenum = message->GetLineNumber(context).FromJust();
        fprintf(stderr, "%s:%i: %s\n", filename_string, linenum, exception_string);

        // Print line of source code.
        String::Utf8Value sourceline(
                message->GetSourceLine(context).ToLocalChecked());
        const char* sourceline_string = UtilMethods::ToCString(sourceline);
        fprintf(stderr, "%s\n", sourceline_string);

        // Print wavy underline (GetUnderline is deprecated).
        int start = message->GetStartColumn(context).FromJust();
        for (int i = 0; i < start; i++) {
            fprintf(stderr, " ");
        }
        int end = message->GetEndColumn(context).FromJust();
        for (int i = start; i < end; i++) {
            fprintf(stderr, "^");
        }
        fprintf(stderr, "\n");
        Local<Value> stack_trace_string;
        if (try_catch->StackTrace(context).ToLocal(&stack_trace_string) &&
            stack_trace_string->IsString() &&
            Local<String>::Cast(stack_trace_string)->Length() > 0) {
            String::Utf8Value stack_trace(stack_trace_string);
            const char* stack_trace_string = UtilMethods::ToCString(stack_trace);
            fprintf(stderr, "%s\n", stack_trace_string);
        }
    }
}