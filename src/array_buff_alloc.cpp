#include "array_buff_alloc.h"
#include <stdlib.h>
#include <string.h>
using namespace v8;

void* ArrayBufferAllocator::Allocate(size_t length) {
    void* data = AllocateUninitialized(length);
    return data == NULL ? data : memset(data, 0, length);
}

void* ArrayBufferAllocator::AllocateUninitialized(size_t length) { 
    return malloc(length); 
}

void ArrayBufferAllocator::Free(void* data, size_t) { 
    free(data); 
}
