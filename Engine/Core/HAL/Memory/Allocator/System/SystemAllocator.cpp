#include "stdafx.h"
#include "SystemAllocator.h"

#include <stdlib.h>

SystemAllocator::SystemAllocator()
{
}

SystemAllocator::~SystemAllocator()
{
}

void* SystemAllocator::Malloc(size_t Size)
{
	return ::malloc(Size);
}

void* SystemAllocator::Realloc(void* Original, size_t Size)
{
	return ::realloc(Original, Size);
}

void SystemAllocator::Free(void* Original)
{
	::free(Original);
}