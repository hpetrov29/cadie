#pragma once
#include <filesystem>

#ifdef CADIE_PLATFORM_WINDOWS
#if CADIE_DYNAMIC_LINK
	#ifdef CADIE_BUILD_DLL
		#define CADIE_API _declspec(dllexport)
	#else
		#define CADIE_API _declspec(dllimport)
	#endif
#else
	#define CADIE_API
#endif
#else
	#error Cadie is supported only on Windows
#endif

#define BIT(x) (1 << x)

#ifdef CADIE_DEBUG
	#if defined(CADIE_PLATFORM_WINDOWS)
		#define CADIE_DEBUGBREAK() __debugbreak()
	#endif
	#define CADIE_ENABLE_ASSERTS
	#else
		#define CADIE_DEBUGBREAK()
#endif

#define CADIE_EXPAND_MACRO(x) x
#define CADIE_STRINGIFY_MACRO(x) #x

#ifdef CADIE_ENABLE_ASSERTS

// Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
#define CADIE_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { CADIE##type##ERROR(msg, __VA_ARGS__); CADIE_DEBUGBREAK(); } }
#define CADIE_INTERNAL_ASSERT_WITH_MSG(type, check, ...) CADIE_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
#define CADIE_INTERNAL_ASSERT_NO_MSG(type, check) CADIE_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", CADIE_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

#define CADIE_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
#define CADIE_INTERNAL_ASSERT_GET_MACRO(...) CADIE_EXPAND_MACRO( CADIE_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, CADIE_INTERNAL_ASSERT_WITH_MSG, CADIE_INTERNAL_ASSERT_NO_MSG) )

// Currently accepts at least the condition and one additional parameter (the message) being optional
#define CADIE_ASSERT(...) CADIE_EXPAND_MACRO( CADIE_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
#define CADIE_CORE_ASSERT(...) CADIE_EXPAND_MACRO( CADIE_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
#define CADIE_ASSERT(...)
#define CADIE_CORE_ASSERT(...)
#endif