//
// Created by chrisvm on 04-24-16.
//

#ifndef GRAPEFRUIT_JS_UTIL_METHODS_H
#define GRAPEFRUIT_JS_UTIL_METHODS_H
#include <stdio.h>
#include <stdlib.h>

namespace std {
    class UtilMethods {
    public:
        static char *fileToBuffer(char const *file);
        static char *fileToBuffer(char const *file, int &size);
    };
};

#endif //GRAPEFRUIT_JS_UTIL_METHODS_H
