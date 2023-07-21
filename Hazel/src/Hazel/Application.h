#pragma once

#include "Core.h"
#include "Window.h"

#include "LayerStack.h"
#include "Event/Event.h"
#include "Event/ApplicationEvent.h"

namespace Hazel
{


	class HAZEL_API Application
	{
	public:
		Application();
		virtual ~Application();

		// 运行
		void Run();

		// 被Winodw类所回调的函数
		void OnEvent(Event& e);

		// Layer
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

	private:
		bool OnWindowClosed(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;

		LayerStack m_LayerStack;

	};

	// TO be define in Client
	Application* CreateApplicaiton();
}
