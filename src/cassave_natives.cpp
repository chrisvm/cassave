#include "cassave_natives.h"


/**
 * Get the source code of the bindings given by param
 * @param args FunctionCallbackInfo - the type of bindig to get
 * @return ModuleSource[] - array with sourcode structs
 */
void Natives::GetBindings(const FunctionCallbackInfo<Value>& args) {
	// get first argument as string
	Local<String> module = args[0]->ToString(args.GetIsolate());

	
}

/**
 * Get listing of all native modules
 * @return char*[] - an array with the structure {module_name, module_path, ...}
 */
const char*[] Natives::NativeList() {
	const char*[] = {
		""
	};
}
