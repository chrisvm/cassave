#include "v8_methods.h"

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