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

		// 当此层推送到堆栈上时
		virtual void OnAttach(){}
		// 当此层移除时
		virtual void OnDetach(){}
		// 层更新，每帧调用
		virtual void OnUpdate(){}
		// 此层用于接受事件时
		virtual void OnEvent(Event& event){}
		// 用于任何ImGui的渲染
		virtual void OnImGuiRender(){}

		inline const std::string& GetName() const { return m_DebugName; }

	protected:
		std::string m_DebugName;


	};

}
