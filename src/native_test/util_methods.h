//
// Created by chrisvm on 04-24-16.
//

#ifndef GRAPEFRUIT_JS_UTIL_METHODS_H
#define GRAPEFRUIT_JS_UTIL_METHODS_H

#include <include/v8.h>
#include <include/libplatform/libplatform.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
using namespace v8;

namespace std {
    class UtilMethods {
    public:
        static char *fileToBuffer(char const *file);
        static char *fileToBuffer(char const *file, int &size);
        static const char *ToCString(String::Utf8Value &value);
    };
};

#endif //GRAPEFRUIT_JS_UTIL_METHODS_H
