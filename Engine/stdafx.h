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
#include "Core/HAL/File/GenericFile.h"

#include "Core/HAL/AppWindow/GenericWindow.h"

#include "Core/RHI/RHIDefinitions.h"
#include "Core/RHI/VertexLayout.h"
#include "Core/RHI/DynamicRHI.h"

#include "Core/CoreGlobal.h"

#if USE_VULKAN
	#define GLFW_INCLUDE_VULKAN
	#include <GLFW/glfw3.h>
#endif