#include "stdafx.h"
#include "CoreGlobal.h"

#include "HAL/Memory/Memory.h"

Memory GMemory;

#pragma region New/Delete Operator

void* operator new(size_t size) //throw(std::bad_alloc)
{
	return GMemory.Malloc(size);
}

void* operator new(size_t size, const std::nothrow_t&) throw()
{
	return GMemory.Malloc(size);
}

void* operator new[](size_t size) //throw(std::bad_alloc) 
{
	return GMemory.Malloc(size);
}

void* operator new[](size_t size, const std::nothrow_t&) throw()
{
	return GMemory.Malloc(size);
}

void operator delete(void* ptr) //throw(std::bad_alloc) 
{
	GMemory.Free(ptr);
}

void operator delete(void* ptr, const std::nothrow_t&) throw()
{
	GMemory.Free(ptr);
}

void operator delete[](void* ptr) //throw(std::bad_alloc) 
{
	GMemory.Free(ptr);
}

void operator delete[](void* ptr, const std::nothrow_t&) throw()
{
	GMemory.Free(ptr);
}

#pragma endregion