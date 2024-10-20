#pragma once
#include <Core/Logger.h>

#ifdef EMSCRIPTEN
#define PLATFORM_BROWSER
#endif

#ifdef DEBUG
#define ENABLE_ASSERTS
#endif

#ifdef ENABLE_ASSERTS
	//#define ASSERT(x,...) { if (!(x)) { ERROR("Assertion Failed: {0}",__VA_ARGS__); __debugbreak();} } 
	//#define CORE_ASSERT(x,...) { if (!(x)) { ERROR("Core Assertion Failed: {0}", __VA_ARGS__); __debugbreak();} } 
	#define ASSERT(x, ...) 
	#define CORE_ASSERT(x, ...)
#else
	#define ASSERT(x, ...) 
	#define CORE_ASSERT(x, ...)
#endif



template<typename T>
using Scope = std::unique_ptr<T>;
template<typename T, typename ... Args>
constexpr Scope<T> CreateScope(Args&& ... args)
{
	return std::make_unique<T>(std::forward<Args>(args)...);
}

template<typename T>
using Ref = std::shared_ptr<T>;
template<typename T, typename ... Args>
constexpr Ref<T> CreateRef(Args&& ... args)
{
	return std::make_shared<T>(std::forward<Args>(args)...);
}
