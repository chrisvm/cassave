#include "util_methods.h"
using namespace std;

char* UtilMethods::fileToBuffer(char const * file, int &size) {
    FILE *fptr;
    char *buf;

    // open file
    fptr = fopen(file, "rb");

    // return null if error opening
    if (!fptr) {
        return NULL;
    }

    // get length of file
    fseek(fptr, 0, SEEK_END);
    size = ftell(fptr);

    // allocate mem and read
    buf = (char*) malloc(size + 1);
    fseek(fptr, 0, SEEK_SET);
    fread(buf, size, 1, fptr);

    // close the file
    fclose(fptr);

    // null terminator
    buf[size] = 0;

    return buf;
}

char* UtilMethods::fileToBuffer(char const * file) {
    FILE *fptr;
    long length;
    char *buf;

    // open file
    fptr = fopen(file, "rb");

    // return null if error opening
    if (!fptr) {
        return NULL;
    }

    // get length of file
    fseek(fptr, 0, SEEK_END);
    length = ftell(fptr);

    // allocate mem and read
    buf = (char*) malloc(length + 1);
    fseek(fptr, 0, SEEK_SET);
    fread(buf, length, 1, fptr);

    // close the file
    fclose(fptr);

    // null terminator
    buf[length] = 0;

    return buf;
}