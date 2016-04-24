#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <include/libplatform/libplatform.h>
#include <include/v8.h>
using namespace v8;

Platform* init(int argc, char* argv[]);
void deinit(Platform *&platform);

int main(int argc, char* argv[]) {
	// init v8 and create platform
	Platform *platform = init(argc, argv);
	
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

    return platform;
}

void deinit(Platform *&platform) {
	V8::Dispose();
    V8::ShutdownPlatform();
    delete platform;
}