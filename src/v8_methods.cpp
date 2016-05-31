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

    // set global methods
    global->Set(isolate, "write", FunctionTemplate::New(isolate, IONativeBinding::Write));
    global->Set(isolate, "print", FunctionTemplate::New(isolate, IONativeBinding::Print));
    global->Set(isolate, "writef", FunctionTemplate::New(isolate, IONativeBinding::WriteF));

	// set global process object
	Local<ObjectTemplate> process = ObjectTemplate::New(isolate);

    // set process.binding function
    process->Set(isolate, "binding", FunctionTemplate::New(isolate, Binding));

    // add process object to global namespace
	global->Set(isolate, "process", process);

	return Context::New(isolate, NULL, global);
}

static void Binding(const FunctionCallbackInfo<Value>& args) {
    // isolate from args
    Isolate *isolate = args.GetIsolate();

    // get name of module
    Local<String> mod_name = args[0]->ToString(isolate);

    // exports is the object that is returned by the call to binding
    Local<Object> exports;

    // if native binding name, return that
    int index;
}