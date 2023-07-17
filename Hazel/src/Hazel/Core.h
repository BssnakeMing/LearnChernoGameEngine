#pragma once

// 辅助代码.h文件

// 不同项目构建时使用的参数，对照是DLL文件
#ifdef HZ_PLATFORM_WINDOWS
	#ifdef HZ_BUID_DLL
		#define HAZEL_API __declspec(dllexport)
	#else
		#define HAZEL_API __declspec(dllimport)
	#endif
#else
	#error Hazel only support Windows!
#endif

// 检查一个条件是否成立，F则触发断言并打印
#ifdef HZ_ENABLE_ASSERTS
	#define HA_ASSERTS(x, ...) { if(!(x)) { HZ_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define HZ_CORE_ASSERT(x, ...) { if(!(x)) { HZ_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define HA_ASSERTS(x, ...)
	#define HZ_CORE_ASSERT(x, ...)
#endif




#define BIT(x) (1 << x)
