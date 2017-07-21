#include "stdafx.h"
#include "Memory.h"

#include "../Allocator/BaseAllocator.h"
#include "../Allocator/TBB/TBBAllocator.h"

Memory::Memory()
{
}

Memory::~Memory()
{
}

void Memory::Init()
{
    InitAllocator();
}

void Memory::Destroy()
{
    SAFE_DELETE(m_Allocator);
}

void* Memory::Malloc(size_t Size)
{
    if (m_Allocator == nullptr)
    {
        ::malloc(m_Allocator);
    }

    return m_Allocator->Malloc(Size);
}

void* Memory::Realloc(void * Original, size_t Size)
{
    return m_Allocator->Realloc(Original, Size);
}

void Memory::Free(void * Original)
{
    return m_Allocator->Free(Original);
}

void Memory::InitAllocator()
{
    m_Allocator = new TBBAllocator();
}