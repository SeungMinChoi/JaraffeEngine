#pragma once

#define ENGINE_NAME "Jaraffe Engine"

#define ENGINE_VERSION_MAJOR 1
#define ENGINE_VERSION_MINOR 0
#define ENGINE_VERSION_PATCH 0

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#ifdef _DEBUG
	#define USE_LOG 1
#else
	#define USE_LOG 0
#endif

#define USE_VULKAN 1