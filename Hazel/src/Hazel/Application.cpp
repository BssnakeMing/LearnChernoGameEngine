
#include "hzpch.h"
#include "Application.h"

#include "Hazel/Event/ApplicationEvent.h"
#include "Hazel/Log.h"

Hazel::Application::Application()
{

}

Hazel::Application::~Application()
{
}

void Hazel::Application::Run()
{
	WindowResizeEvent e(1280, 720);
	HZ_TRACE(e);

	while (true);
}
