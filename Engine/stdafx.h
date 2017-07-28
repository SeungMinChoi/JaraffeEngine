#pragma once

// Base
#include <iostream>
#include <functional>

#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <chrono>
#include <vector>
#include <cstring>
#include <array>
#include <set>
#include <unordered_map>

// Config
#include "Config/EngineConfig.h"

// Common
#include "Common/GlobalMacro.h"

//
#include "Core/AppWindow/GenericWindow.h"
#include "Core/GraphicDevice/GenericGraphicDevice.h"
#include "Core/CoreGlobal.h"

#if USE_VULKAN
	#define GLFW_INCLUDE_VULKAN
	#include <GLFW/glfw3.h>
#endif