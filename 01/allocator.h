#pragma once
#include <stdlib.h>

class Allocator
{
    size_t max_size = 0, offset = 0;
    char* pointer = nullptr;
public:
    void makeAllocator(size_t maxSize)
    {
        if (max_size != 0)
        {
            max_size = 0;
            offset = 0;
            delete(pointer);
        }
        max_size = maxSize;
        pointer = new char[max_size];
        offset = 0;
    }

    char* alloc(size_t size)
    {
        if (offset + size > max_size)
            return nullptr;

        char* result = pointer;
        result += offset;
        offset += size;
        return result;
    }

    void reset()
    {
        offset = 0;
    }

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

    ~Allocator()
    {
        delete(pointer);
    }

};