#pragma once
#include <Core/Logger.h>

#ifdef EMSCRIPTEN
#define PLATFORM_BROWSER
#endif

#ifdef DEBUG
#define ENABLE_ASSERTS
#endif

#ifdef ENABLE_ASSERTS
	#define ASSERT(x,...) { if (!(x)) { ERROR("Assertion Failed: {0}",__VA_ARGS__); __debugbreak();} } 
	#define ASSERT(x,...) { if (!(x)) { ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();} } 
#else
	#define ASSERT(x, ...) 
	#define CORE_ASSERT(x, ...)
#endif
