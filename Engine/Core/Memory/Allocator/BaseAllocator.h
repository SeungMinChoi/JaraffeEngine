#pragma once

class Allocator
{
public:
    virtual void* Malloc(size_t Size) = 0;
    virtual void* Realloc(void* Original, size_t Size) = 0;
    virtual void Free(void* Original) = 0;
};