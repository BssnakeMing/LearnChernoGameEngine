#pragma once

#include "Hazel/Core.h"

#include <string>
#include <functional>

namespace Hazel
{

	// 描述事件类型
	enum class EventType
	{
		None = 0,
		// Windows
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		// App
		AppTick, AppUpdata, AppRender,
		// Key
		KeyPressed, KeyReleased,
		// Mouse
		MouseButtonPressed, MouseButtonReleased, MouseMove, MousesScrolled
	};

	// 事件分类或过滤， 对应EventType枚举的筛选
	enum EventCategory
	{
		None = 0,
		EventCategoryApplication	= BIT(0),
		EventCategoryInput			= BIT(1),
		EventCategoryKeyboard		= BIT(2),
		EventCategoryMouse			= BIT(3),
		EventCategoryMouseButton	= BIT(4)
	};;

	// 用于实现虚函数的宏，只输入给定的事件即可注册重写虚函数
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

	// 注册键盘输入事件的标签
#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	// 所有输入事件的基类
	class HAZEL_API Event
	{
		friend class EventDispatcher;
		// =0 为纯虚函数，不能被实例化
	public:
		// 获取当前输入事件类型
		virtual EventType GetEventType() const = 0;
		// 将当前输入类型转为字符串
		virtual const char* GetName() const = 0;

		virtual int GetCategoryFlags() const = 0;
		// 默认返回事件的名称，重写修改	---debugfunction
		virtual std::string ToString() const { return GetName(); }

		// 检查当前的事件 与 传递的事件相同吗
		// 检查事件分类
		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}

	protected:
		// 事件的传递句柄
		bool m_Handled = false;

	};


	// 基于事件类型调用
	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;

	public:
		EventDispatcher(Event& event):m_Event(event){}


		// 输入事件是否和当前事件匹配
		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetEventType()== T::GetStaticType())
			{
				m_Event.m_Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}

}
