#pragma once

// ��������.h�ļ�

// ��ͬ��Ŀ����ʱʹ�õĲ�����������DLL�ļ�
#ifdef HZ_PLATFORM_WINDOWS
	#ifdef HZ_BUID_DLL
		#define HAZEL_API __declspec(dllexport)
	#else
		#define HAZEL_API __declspec(dllimport)
	#endif
#else
	#error Hazel only support Windows!
#endif

// ���һ�������Ƿ������F�򴥷����Բ���ӡ
#ifdef HZ_ENABLE_ASSERTS
	#define HA_ASSERTS(x, ...) { if(!(x)) { HZ_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define HZ_CORE_ASSERT(x, ...) { if(!(x)) { HZ_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define HA_ASSERTS(x, ...)
	#define HZ_CORE_ASSERT(x, ...)
#endif




#define BIT(x) (1 << x)
