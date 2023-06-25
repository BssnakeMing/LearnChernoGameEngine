#pragma once

#include "Hazel/Core.h"

#include <string>
#include <functional>

namespace Hazel
{

	// �����¼�����
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

	// �¼��������ˣ� ��ӦEventTypeö�ٵ�ɸѡ
	enum EventCategory
	{
		None = 0,
		EventCategoryApplication	= BIT(0),
		EventCategoryInput			= BIT(1),
		EventCategoryKeyboard		= BIT(2),
		EventCategoryMouse			= BIT(3),
		EventCategoryMouseButton	= BIT(4)
	};;

	// ����ʵ���麯���ĺֻ꣬����������¼�����ע����д�麯��
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

	// ע����������¼��ı�ǩ
#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	// ���������¼��Ļ���
	class HAZEL_API Event
	{
		friend class EventDispatcher;
		// =0 Ϊ���麯�������ܱ�ʵ����
	public:
		// ��ȡ��ǰ�����¼�����
		virtual EventType GetEventType() const = 0;
		// ����ǰ��������תΪ�ַ���
		virtual const char* GetName() const = 0;

		virtual int GetCategoryFlags() const = 0;
		// Ĭ�Ϸ����¼������ƣ���д�޸�	---debugfunction
		virtual std::string ToString() const { return GetName(); }

		// ��鵱ǰ���¼� �� ���ݵ��¼���ͬ��
		// ����¼�����
		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}

	protected:
		// �¼��Ĵ��ݾ��
		bool m_Handled = false;

	};


	// �����¼����͵���
	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;

	public:
		EventDispatcher(Event& event):m_Event(event){}


		// �����¼��Ƿ�͵�ǰ�¼�ƥ��
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
