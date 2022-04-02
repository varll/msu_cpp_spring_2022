#include "allocator.h"

    void Allocator::makeAllocator(size_t maxSize)
    {
        if (max_size != 0)
        {
            max_size = 0;
            offset = 0;
            delete[] pointer;
        }
        max_size = maxSize;
        pointer = new char[max_size];
        offset = 0;
    }

    char* Allocator::alloc(size_t size)
    {
        if (offset + size > max_size)
            return nullptr;

        char* result = pointer;
        result += offset;
        offset += size;
        return result;
    }

    void Allocator::reset()
    {
        offset = 0;
    }

    Allocator::~Allocator()
    {
        delete[] pointer;
    }