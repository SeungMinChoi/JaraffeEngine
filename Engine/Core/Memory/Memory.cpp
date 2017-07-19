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

void Memory::InitAllocator()
{
    m_Allocator = new TBBAllocator();
}