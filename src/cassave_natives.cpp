#include "cassave_natives.h"


/**
 * Checks if a js module is defined with name moduleName, a c-string
 */
int CassaveNatives::searchForModule(char* moduleName) {
    // size of the natives modules array
    size_t nativeSize = sizeof(natives);

    // look for module in natives array
    _native* mod;
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
