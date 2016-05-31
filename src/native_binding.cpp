//
// Created by chrisvm on 05-25-16.
//

#include "native_binding.h"

void ModuleSubs::setNativeBinding(char* mod_name, ModFuncCallback cb) {
    mods[mod_name] = cb;
}

bool ModuleSubs::hasNativeBinding(char* mod_name) {
    bool ret = false;
    for (auto kv : mods) {
        if (strcmp(mod_name, kv.first) == 0) {
            ret = true;
            break;
        }
    }

    return ret;
}

ModFuncCallback ModuleSubs::getNativeBinding(char* mod_name) {
    return mods[mod_name];
}