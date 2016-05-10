//
// Created by chrisvm on 04-25-16.
//

#ifndef CASSAVE_JS_GLOBAL_FUNCS_H
#define CASSAVE_JS_GLOBAL_FUNCS_H
#include "include/v8.h"
#include "include/libplatform/libplatform.h"
#include "util_methods.h"

#include <stdarg.h>
#include <list>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace v8;
using namespace std;

static void Print(const FunctionCallbackInfo<Value>& args);
static void PrintL(const FunctionCallbackInfo<Value>& args);
static void PrintFormat(const FunctionCallbackInfo<Value>& args);

#endif //CASSAVE_JS_GLOBAL_FUNCS_H
