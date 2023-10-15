#pragma once
#include "Hazel/PlathForm/Windows/WindowsWindow.h"
#include "Hazel/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Hazel
{


	class OpenGLContext :public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);


		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		// GLFW Window
		GLFWwindow* m_WindowHandle;
		 
	};
}