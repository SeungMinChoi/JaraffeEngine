#pragma once

class DynamicRHI
{
public:
    DynamicRHI();
    virtual ~DynamicRHI();

public:
    virtual void Init(void* WindowHandle) = 0;
    virtual void Draw() = 0;
    virtual void Destroy() = 0;

    virtual void Resize() = 0;
};