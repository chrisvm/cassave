//
// Created by chrisvm on 05-25-16.
//

#ifndef CASSAVE_JS_NATIVEBINDING_H
#define CASSAVE_JS_NATIVEBINDING_H
#include <include/v8.h>
#include <include/libplatform/libplatform.h>
#include <map>
#include <cstring>
using namespace v8;

class NativeBinding;

// function callback typdef
typedef void (NativeBinding::*ModFuncCallback)(Isolate*, Local<Object>);

class ModuleSubs {
    std::map<char*, ModFuncCallback> mods;

public:
    /**
     * Sets a binding with name
     */
    void setNativeBinding(char* mod_name, ModFuncCallback cb);

    /**
     * Returns -1 if not found, the index in mods if found
     */
    bool hasNativeBinding(char* mod_name);

    /**
     * Get the binding setting callback
     */
    ModFuncCallback getNativeBinding(char* mod_name);
};


class NativeBinding {
public:
    NativeBinding(ModuleSubs *m_subs) {
        // set module
        m_subs->setNativeBinding(this->getName(), &NativeBinding::setTarget);
    }

    virtual void setTarget(Isolate *isolate, Local<Object> target)=0;
    virtual char* getName()=0;
};


#endif //CASSAVE_JS_NATIVEBINDING_H
