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