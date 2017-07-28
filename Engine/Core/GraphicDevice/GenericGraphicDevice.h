#pragma once

class GenericGraphicDevice
{
public:
	GenericGraphicDevice();
	virtual ~GenericGraphicDevice();

public:
	virtual void Init(void* WindowHandle) = 0;
	virtual void Destroy() = 0;
};