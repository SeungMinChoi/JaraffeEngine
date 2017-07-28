#pragma once

#define SAFE_DELETE(x)  \
if(x)                   \
{                       \
    delete x;           \
    x = nullptr;        \
}

//std::bind(std::mem_fn(&DebugCallback), this, std::placeholders::_1, std::placeholders::_2);