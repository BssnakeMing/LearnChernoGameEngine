#pragma once

#include "Event.h"

#include <sstream>

namespace Hazel
{

	// 按下键盘一个键时触发事件，所有键盘相应的基类
	class HAZEL_API KeyEvent:public Event
	{
	public:
		inline int GetKeyCode() const { return m_KeyCore; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	private:
		KeyEvent(int keycode)
			:keycode(keycode){}

		// 按下的键
		int m_KeyCode;
	};

	class HAZEL_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keyCode, int repeatCound)
			:KeyEvent(keyCode),m_RepeatCount(repeatCound){}

		inline int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			// 打印已按下的Key队列
			ss << "KeyPressedEvent" << m_KeyCode << "(" << m_RepeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)

	private:
		// 按下计数
		int m_RepeatCount;
	};


	class HAZEL_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keyCode)
			:KeyEvent(keyCode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			// 打印已按下的Key队列
			ss << "KeyReleasedEvent" << m_KeyCode << "(" << m_RepeatCound << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased);

	};

}
