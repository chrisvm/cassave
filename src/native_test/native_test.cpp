#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <include/libplatform/libplatform.h>
#include <include/v8.h>

#include "./array_buff_alloc.h"
using namespace v8;


// methods for initing and destroying v8
Platform* init(int argc, char* argv[]);
void deinit(Platform *&platform);

// create an Isolate and set array buffer allocator
Isolate* create_isolate();

int main(int argc, char* argv[]) {
	// init v8 and create platform
	Platform *platform = init(argc, argv);
	
	// create isolate
	Isolate* isolate = create_isolate();
	
	// delete platform and turn down v8
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