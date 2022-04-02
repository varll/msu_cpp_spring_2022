#pragma once
#include <stdlib.h>
#include <iostream>

class Allocator
{
    size_t max_size = 0, offset = 0;
    char* pointer = nullptr;
public:
    void makeAllocator(size_t maxSize);

    char* alloc(size_t size);

    void reset();

    size_t get_size()
    {
        return max_size;
    }

    size_t get_offset()
    {
        return offset;
    }

    char* get_pointer()
    {
        return pointer;
    }

    ~Allocator();

};