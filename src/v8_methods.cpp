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
    // check  # of args
    if (args.Length() < 1) {
        return;
    }

    // isolate from args
    Isolate *isolate = args.GetIsolate();

    // get name of module
    String::Utf8Value mod_name(args[0]->ToString());

    // exports is the object that is returned by the call to binding
    Local<Object> exports;

    // get string
    string c_mod_name(*mod_name);

    // search for module
    SubsManager manager;

    // if native binding name, return that
    if (manager.hasSub((char*)c_mod_name.c_str())) {
        // create new object to pass to the subscribed module func
        exports = Object::New(isolate);

        // pass to subscribed func
        manager.setBinding((char*)c_mod_name.c_str(), isolate, exports);
    } else if (c_mod_name == "natives") {
        // return an object with all bundled js source
    }

    // set a return val
    args.GetReturnValue().Set(exports);
}