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


#ifdef HZ_ENABLE_ASSERTS // we use this macro for debug mode only
	#define HZ_ASSERT(x, ...) { if (!(x)) { HZ_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
	#define LOG_ASSERT(x, ...) { if (!(x)) { LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
	// "if (!(x))" --> if the given arg condition is false
	// "__debugbreak()" --> similar to adding a breakpoint at the line of code
#else // for releases we can just declare to empty definitions
	#define HZ_ASSERT(x, ...) 
	#define LOG_ASSERT(x, ...)
	// note: since we are using empty def, make sure not call functions within the arg param
	// rather store the final value in a temp value and then send it as arg to macro arg
	// if u want it to support that functionality, use this def below 
	// to avoid the macro getting compiled to nothing ` #define ASSERT(x, ...) x `
#endif

#define BIT(x) (1 << x) // returns 2^x representing 1 bit in x's position from LSB