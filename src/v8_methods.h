#ifndef CASSAVE_JS_V8_METHODS_H
#define CASSAVE_JS_V8_METHODS_H
#include <include/v8.h>
#include <include/libplatform/libplatform.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "global_funcs.h"
#include "array_buff_alloc.h"
using namespace v8;
using namespace std;


Platform* init(int argc, char* argv[]);
void deinit(Platform *&platform);
Isolate* create_isolate();
Local<Context> create_context(Isolate *isolate);




#endif
