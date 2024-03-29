#pragma once

#include "Event.h"



namespace Hazel
{

	// 按下键盘一个键时触发事件，所有键盘相应的基类
	class HAZEL_API KeyEvent:public Event
	{
	public:
		inline int GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
		
	protected:
		KeyEvent(int keycode)
			:m_KeyCode(keycode){}

		// 按下的键
		int m_KeyCode;
	};

	class HAZEL_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode, int repeatCount)
			:KeyEvent(keycode),m_RepeatCount(repeatCount){}

		inline int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			// 打印已按下的Key队列
			ss << "KeyPressedEvent: " << m_KeyCode << "(" << m_RepeatCount << " repeats)";
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
			ss << "KeyReleasedEvent: " << m_KeyCode ;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)

	};

	class HAZEL_API KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(int keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};

}
