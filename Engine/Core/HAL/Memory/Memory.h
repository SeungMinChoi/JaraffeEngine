#pragma once

class Memory
{
public:
    Memory();
    virtual ~Memory();

public:
    void* Malloc(size_t Size);
    void* Realloc(void* Original, size_t Size);
    void Free(void* Original);
};