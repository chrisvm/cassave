#ifndef __NATIVE_REQUIRE_H
#define __NATIVE_REQUIRE_H
#include <vector>
#include "v8.h"
using namespace std;
using namepspace v8;

// Module to hold name (id) of the module and a
// pointer to the instance of the module
struct NativeSource {
	char *name;
	vector<char*> source;
};

// Native require, which the js 'require' module uses
// to bootstrap all other modules
class NativeRequire {
	vector<NativeModuleReference> native_modules;

	void initNative();
public:
	NativeRequire();

};
#endif
