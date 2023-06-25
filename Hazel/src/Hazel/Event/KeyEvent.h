#pragma once

#include "Event.h"

#include <sstream>

namespace Hazel
{

	// ���¼���һ����ʱ�����¼������м�����Ӧ�Ļ���
	class HAZEL_API KeyEvent:public Event
	{
	public:
		inline int GetKeyCode() const { return m_KeyCore; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	private:
		KeyEvent(int keycode)
			:keycode(keycode){}

		// ���µļ�
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
			// ��ӡ�Ѱ��µ�Key����
			ss << "KeyPressedEvent" << m_KeyCode << "(" << m_RepeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)

	private:
		// ���¼���
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
			// ��ӡ�Ѱ��µ�Key����
			ss << "KeyReleasedEvent" << m_KeyCode << "(" << m_RepeatCound << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased);

	};

}
