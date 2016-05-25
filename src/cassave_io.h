//
// Created by chrisvm on 05-25-16.
//

#ifndef CASSAVE_JS_CASSAVE_IO_H_H
#define CASSAVE_JS_CASSAVE_IO_H_H
#include <include/v8.h>
#include <include/libplatform/libplatform.h>
#include "native_binding.h"
using namespace std;
using namespace v8;

class IONativeBinding : public NativeBinding {
public:
    char* getName();
    static void getInstance();

    static void Write(const FunctionCallbackInfo<Value>& args);
    static void Print(const FunctionCallbackInfo<Value>& args);
    static void WriteF(const FunctionCallbackInfo<Value>& args);
};

#endif //CASSAVE_JS_CASSAVE_IO_H_H
