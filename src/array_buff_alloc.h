#ifndef __ARRAY_BUFF_ALLOC_H
#define __ARRAY_BUFF_ALLOC_H
#include <include/libplatform/libplatform.h>
#include <include/v8.h>
using namespace v8;

class ArrayBufferAllocator : public v8::ArrayBuffer::Allocator {
public:
    virtual void* Allocate(size_t length);
    virtual void* AllocateUninitialized(size_t length);
    virtual void Free(void* data, size_t);
};

#endif