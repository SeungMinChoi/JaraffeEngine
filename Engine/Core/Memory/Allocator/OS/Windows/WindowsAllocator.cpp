#include "stdafx.h"
#include "WindowsAllocator.h"

#include <memory>

void* WindowsAllocator::Malloc(size_t Size)
{
    return ::malloc(Size);
}

void* WindowsAllocator::Realloc(void* Original, size_t Size)
{
    return ::realloc(Original, Size);
}

void WindowsAllocator::Free(void* Original)
{
    free(Original);
}