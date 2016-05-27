#include "cassave_natives.h"


/**
 * Checks if a js module is defined with name moduleName, a c-string
 */
int CassaveNatives::searchForModule(char* moduleName) {
    // size of the natives modules array
    size_t nativeSize = sizeof(natives);

    // look for module in natives array
    const _native* mod;
    for (int index = 0; index < nativeSize; ++index) {
        // get module
        mod = &natives[index];

        // compare module names
        if (strcmp(mod->name, moduleName) == 0) {
            // found a module with name moduleName
            return index;
        }
    }

    // not found
    return -1;
}

/**
 * Sets to target all the modules packaged with the cassave binary
 */
static void defineJavascriptSource(Isolate *isolate, Local<Object> target) {
    // a new scope for all the handles well create
    HandleScope scope(isolate);

    // iterate all the native modules in natives array
    for (auto module : natives) {
        // the name of the module
        Local<String> name = String::NewFromUtf8(isolate, module.name);

        // the actual js source in a js string
        Local<String> source = String::NewFromUtf8(
                isolate,
                reinterpret_cast<const char*>(module.source),
                NewStringType::kNormal,
                module.source_len
        ).ToLocalChecked();

        // set target.<module.name> = <module.source>
        target->Set(name, source);
    }
}