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
    global->Set(isolate, "write", FunctionTemplate::New(isolate, Print));
    global->Set(isolate, "print", FunctionTemplate::New(isolate, PrintL));
    global->Set(isolate,
			"writef",
			FunctionTemplate::New(isolate, PrintFormat));

	// set global process object
	Local<ObjectTemplate> process = ObjectTemplate::New(isolate);
	process->Set(isolate,
			"bindings",
			FunctionTemplate::New(isolate, GetBindings));
	global->Set(isolate, "process", process);

	return Context::New(isolate, NULL, global);
}
