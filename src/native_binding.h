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


class NativeBinding {
public:

    virtual void setTarget(Isolate *isolate, Local<Object> target)=0;
    virtual char* getName()=0;
};


#endif //CASSAVE_JS_NATIVEBINDING_H
