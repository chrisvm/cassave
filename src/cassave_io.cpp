#include "cassave_io.h"

char* IONativeBinding::getName() {
    return (char*)"io";
}

void IONativeBinding::setTarget(Isolate *isolate, Local<Object> target) {
    // set bindings
    target->Set(String::NewFromUtf8(isolate, "write"), FunctionTemplate::New(isolate, IONativeBinding::Write)
            ->GetFunction());
    target->Set(String::NewFromUtf8(isolate, "print"), FunctionTemplate::New(isolate, IONativeBinding::Print)
            ->GetFunction());
    target->Set(String::NewFromUtf8(isolate, "writef"), FunctionTemplate::New(isolate, IONativeBinding::WriteF)
            ->GetFunction());
}

void IONativeBinding::Write(const FunctionCallbackInfo<Value>& args) {
    bool first = true;
    for (int i = 0; i < args.Length(); i++) {
        HandleScope handle_scope(args.GetIsolate());

        if (first) {
            first = false;
        } else {
            printf(" ");
        }

        String::Utf8Value str(args[i]);
        const char* c_str = UtilMethods::ToCString(str);
        printf("%s", c_str);
    }
    fflush(stdout);
}

void IONativeBinding::Print(const FunctionCallbackInfo<Value>& args) {
    bool first = true;
    for (int i = 0; i < args.Length(); i++) {
        HandleScope handle_scope(args.GetIsolate());

        if (first) {
            first = false;
        } else {
            printf(" ");
        }

        String::Utf8Value str(args[i]);
        const char* c_str = UtilMethods::ToCString(str);
        printf("%s", c_str);
    }
    printf("\n");
    fflush(stdout);
}

void IONativeBinding::WriteF(const FunctionCallbackInfo<Value>& args) {
    bool first = true;
    string format;

    Isolate *isolate = args.GetIsolate();
    HandleScope handle_scope(isolate);
    list<const char *> format_data;


    // extract format and data
    for (int i = 0; i < args.Length(); ++i) {

        String::Utf8Value str(args[i]);
        const char* c_str = UtilMethods::ToCString(str);

        if (first) {
            first = false;
            format = string(c_str);
        } else {
            string t_str(c_str);
            format_data.push_back(t_str.c_str());
        }
    }
;
    // render format
    unsigned long length = format.length();
    for (int i = 0; i < length; i += 1) {
        char at = format[i];
        switch (at) {
            case '%':
                if (format[i + 1] == '%') {
                    printf("%c", '%');
                    i += 1;
                } else {
                    if (format_data.empty()) {
                        isolate->ThrowException(String::NewFromUtf8(isolate, "Missing printf values for format"));
                        return;
                    }

                    printf("%s", format_data.front());
                    format_data.pop_front();
                }
                break;

            default:
                printf("%c", at);
                break;
        }
    }

    fflush(stdout);
}
