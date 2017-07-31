#include "stdafx.h"
#include "TBBAllocator.h"

#include "tbb/scalable_allocator.h"

TBBAllocator::TBBAllocator()
{
}

TBBAllocator::~TBBAllocator()
{
}

void* TBBAllocator::Malloc(size_t Size)
{
    return scalable_malloc(Size);
}

void* TBBAllocator::Realloc(void* Original, size_t Size)
{
    return scalable_realloc(Original, Size);
}

void TBBAllocator::Free(void* Original)
{
    scalable_free(Original);
}