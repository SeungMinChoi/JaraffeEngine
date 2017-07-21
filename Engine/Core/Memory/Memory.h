#pragma once

class Allocator;

class Memory
{
public:
    Memory();
    virtual ~Memory();

public:
    void Init();
    void Destroy();

public:
    void* Malloc(size_t Size);
    void* Realloc(void* Original, size_t Size);
    void Free(void* Original);

private:
    void InitAllocator();

public:
    Allocator* m_Allocator = nullptr;
};