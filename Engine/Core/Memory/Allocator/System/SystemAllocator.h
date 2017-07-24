#pragma once

class SystemAllocator
{
private:
	SystemAllocator();
	~SystemAllocator();

public:
	static void* Malloc(size_t Size);
	static void* Realloc(void * Original, size_t Size);
	static void Free(void * Original);
};