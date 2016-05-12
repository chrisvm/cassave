#ifndef CASSAVE_NATIVES_H
#define CASSAVE_NATIVES_H
#include <include/v8.h>
#include <include/libplatform/libplatform.h>
#include <vector>
using namespace std;
using namespace v8;

struct ModuleSource {
	char* name;
	char*[] source;

	ModuleSource(char* name, char*[] source) {
		this->name = name;
		this->source = source;
	}
};

class Natives {
public:
	// get natives to
	static void GetBindings(const FunctionCallbackInfo<Value>& args);
	static const char*[] NativeList();
};
#endif
