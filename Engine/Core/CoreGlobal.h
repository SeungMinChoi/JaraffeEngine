#pragma once

#include "Core/Memory/Memory.h"

extern Memory* GMemory;

void* operator new(size_t size) throw(std::bad_alloc) { GMemory->m_Allocator->Malloc(size); }
void* operator new(size_t size, const std::nothrow_t&) throw();
void* operator new[](size_t size) throw(std::bad_alloc);
void* operator new[](size_t size, const std::nothrow_t&) throw();
void operator delete(void* ptr) throw(std::bad_alloc);
void operator delete(void* ptr, const std::nothrow_t&) throw();
void operator delete[](void* ptr) throw(std::bad_alloc);
void operator delete[](void* ptr, const std::nothrow_t&) throw();