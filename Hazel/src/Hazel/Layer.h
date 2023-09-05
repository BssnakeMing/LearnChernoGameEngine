#pragma once

#include "Hazel/Core.h"
#include "Hazel/Events/Event.h"


namespace Hazel
{
	
	class HAZEL_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		// ���˲����͵���ջ��ʱ
		virtual void OnAttach(){}
		// ���˲��Ƴ�ʱ
		virtual void OnDetach(){}
		// ����£�ÿ֡����
		virtual void OnUpdate(){}
		// �˲����ڽ����¼�ʱ
		virtual void OnEvent(Event& event){}
		// �����κ�ImGui����Ⱦ
		virtual void OnImGuiRender(){}

		inline const std::string& GetName() const { return m_DebugName; }

	protected:
		std::string m_DebugName;


	};

}
