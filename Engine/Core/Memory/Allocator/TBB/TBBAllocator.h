#pragma once

#include "../BaseAllocator.h"

class TBBAllocator : public Allocator
{
public:
    TBBAllocator();
    virtual ~TBBAllocator();

public:
    virtual void* Malloc(size_t Size) override;
    virtual void* Realloc(void* Original, size_t Size) override;
    virtual void Free(void* Original) override;
};