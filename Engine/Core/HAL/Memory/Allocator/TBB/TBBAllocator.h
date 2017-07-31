#pragma once

class TBBAllocator
{
private:
    TBBAllocator();
    ~TBBAllocator();

public:
    static void* Malloc(size_t Size);
	static void* Realloc(void* Original, size_t Size);
	static void Free(void* Original);
};