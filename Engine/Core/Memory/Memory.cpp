#include "stdafx.h"
#include "Memory.h"

#include "Allocator/TBB/TBBAllocator.h"

Memory::Memory()
{
}

Memory::~Memory()
{
}

void* Memory::Malloc(size_t Size)
{
    return TBBAllocator::Malloc(Size);
}

void* Memory::Realloc(void * Original, size_t Size)
{
    return TBBAllocator::Realloc(Original, Size);
}

void Memory::Free(void * Original)
{
	TBBAllocator::Free(Original);
}