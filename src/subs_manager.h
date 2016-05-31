//
// Created by chrisvm on 05-30-16.
//

#ifndef CASSAVE_JS_SUBSMANAGER_H
#define CASSAVE_JS_SUBSMANAGER_H
#include <include/v8.h>
#include <include/libplatform/libplatform.h>
#include "native_binding.h"
#include "cassave_io.h"
using namespace v8;
using namespace std;

class SubsManager {
    ModuleSubs subs_;
    NativeBinding *bindings_[1];
public:
    SubsManager();
    ~SubsManager();

    void setBinding(char *mod_name, Isolate *isolate, Local<Object> target);
    bool hasSub(char *mod_name);
};


#endif //CASSAVE_JS_SUBSMANAGER_H
