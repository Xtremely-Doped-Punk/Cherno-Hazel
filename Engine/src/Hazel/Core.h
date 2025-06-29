#pragma once

#ifdef HZ_PLATFORM_WINDOWS
	// define api variable to dll-import/export based on macros
	#ifdef HZ_BUILD_DLL
		#define HAZEL_API __declspec(dllexport)
	#else
		#define HAZEL_API __declspec(dllimport)

	#endif // HZ_BUILD_DLL
#else
	#error 'Hazel' only supports Windows!
#endif // HZ_PLATFORM_WINDOWS
