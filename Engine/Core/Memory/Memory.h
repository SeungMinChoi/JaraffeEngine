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

private:
    void InitAllocator();

public:
    Allocator* m_Allocator;
};