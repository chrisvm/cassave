#ifndef CASSAVE_NATIVES_H
#define CASSAVE_NATIVES_H
#include <include/v8.h>
#include <include/libplatform/libplatform.h>
#include <list>
#include "cassave_lib.h"
#include <cstring>
using namespace std;
using namespace v8;

/**
cassave_lib.h declares a _native struct like this:

    struct _native {
        const char* name;
        const unsigned char* source;
        size_t source_len;
    };

This is declared auto by running the script tools/js2c.py. cassave_lib.h
also declares an array as follows:

    static const _native natives[] = { ... };

cassave_natives.cpp/h are implement a set of methods that check containment
of a native js module in cassave_lib.h.
*/

class CassaveNatives {
public:

    /**
     * Checks if a js module is defined with name moduleName, a c-string
     */
    static int searchForModule(char* moduleName);

    /**
     * Defines all the js modules in javascript strings
     */
    static void defineJavascriptSource(Isolate *isolate, Local<Object> target);

    /**
     * Create a list of all native bindings
     */
};
#endif
