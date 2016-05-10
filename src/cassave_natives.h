#ifndef CASSAVE_NATIVES_H
#define CASSAVE_NATIVES_H
#include <include/v8.h>
#include <include/libplatform/libplatform.h>
#include <vector>
using namespace std;
using namespace v8;

class Natives {
public:
	static void GetNatives(const FunctionCallbackInfo<Value>& args);
	static const char*[] NativeList();
};
#endif
