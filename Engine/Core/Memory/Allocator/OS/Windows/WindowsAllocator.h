#pragma once

#include "../../BaseAllocator.h"

class WindowsAllocator : Allocator
{
    virtual void* Malloc(size_t Size) override;
    virtual void* Realloc(void * Original, size_t Size) override;
    virtual void Free(void * Original) override;
};