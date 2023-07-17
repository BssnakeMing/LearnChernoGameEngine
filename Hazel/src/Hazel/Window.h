#pragma once
#include "hzpch.h"

#include "Hazel/Core.h"
#include "Hazel/Event/Event.h"


namespace Hazel
{
	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "Hazel Engine",
			unsigned int width = 1280,
			unsigned int height = 720)
				:Title(title),Width(width), Height(height)
		{
		}
	};

	// Application 所使用的抽象类
	// 抽象类都不应该包含Application
	class HAZEL_API  Window
	{
	public:
		// 窗口类回调函数，子类赋值和调用
		using EventCallbackFn = std::function<void(Event&)>;

#pragma region 子类重写段落
		// 子类重写
		virtual ~Window() {}
		virtual void OnUpdata() = 0;
		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;
		// window attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;
		// 每个平台实现
		static Window* Create(const WindowProps& props = WindowProps());
#pragma endregion
	};

}