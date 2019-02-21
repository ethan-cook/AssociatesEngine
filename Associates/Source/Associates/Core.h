#pragma once

#ifdef ASSOC_PLATFORM_WINDOWS
	#ifdef ASSOC_BUILD_DLL
		#define ASSOC_API __declspec(dllexport)
	#else
		#define ASSOC_API __declspec(dllimport)
	#endif
#else
#error Associates only is supported on Windows!
#endif

#define BIT(x) (1 << x)

#ifdef ASSOC_ENABLE_ASSERTS
	#define ASSOC_ASSERT(x, ...) {if(!(x)) {ASSOC_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define ASSOC_CORE_ASSERT(x, ...) {if(!(x)) {ASSOC_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define ASSOC_ASSERT(x, ...)
	#define ASSOC_CORE_ASSERT(x, ...)
#endif

#define ASSOC_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)