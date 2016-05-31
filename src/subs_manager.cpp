//
// Created by chrisvm on 05-30-16.
//

#include "subs_manager.h"

SubsManager::SubsManager() {
    // create all bindings
    // io
    IONativeBinding *io_binding = new IONativeBinding(&subs_);
    bindings_[0] = io_binding;
}

SubsManager::~SubsManager() {
    // delete io
    delete bindings_[0];
}

void SubsManager::setBinding(char * mod_name, Isolate *isolate, Local<Object> target) {
    for (auto sub : bindings_) {
        if (strcmp(mod_name, sub->getName()) == 0) {
            sub->setTarget(isolate, target);
        }
    }
}

bool SubsManager::hasSub(char *mod_name) {
    for (auto sub : bindings_) {
        if (strcmp(mod_name, sub->getName()) == 0) {
            return true;
        }
    }
    return false;
}