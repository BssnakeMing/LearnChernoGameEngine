#include "hzpch.h"
#include "WindowsWindow.h"

#include "Hazel/Event/KeyEvent.h"
#include "Hazel/Event/MouseEvent.h"
#include "Hazel/Event/ApplicationEvent.h"

namespace Hazel
{
	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int error,const char* desription)
	{
		HZ_CORE_ERROR("GLFW Error ({0}): {1}", error, desription);
	}

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}
	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		HZ_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if(!s_GLFWInitialized)
		{
			int success = glfwInit();
			// 检查glfw是否初始化成功
			HZ_CORE_ASSERT(success, "Could not intialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

		// 创建一个GLFW窗口
		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);

		// 给GLFW窗口设置自定义参数，因为&的是一个void*, 它可以是任何数据
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

#pragma region 绑定GLFW窗口回调函数
		// 窗口大小改变
		glfwSetWindowSizeCallback(m_Window, 
			[](GLFWwindow* window, int width, int heigth)
			{
				// 获取（回调）窗口自定义参数
				WindowData data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.Width = width;
				data.Height = heigth;
				WindowResizeEvent event(width, heigth);
				data.EventCallback(event);
			}
		);
		// 窗口关闭
		glfwSetWindowCloseCallback(m_Window,
			[](GLFWwindow* window)
			{
				WindowData data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				data.EventCallback(event);
			}
		);
		// 窗口内按下键
		glfwSetKeyCallback(m_Window,
			[](GLFWwindow* window, int key, int scancode, int action, int modes)
			{
				WindowData data = *(WindowData*)glfwGetWindowUserPointer(window);
				switch (action)
				{
					case GLFW_PRESS:
					{
						KeyPressedEvent event(key, 0);
						data.EventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						KeyReleasedEvent event(key);
						data.EventCallback(event);
						break;
					}
					// 该键一直按着
					case GLFW_REPEAT:
					{
						KeyPressedEvent event(key, 1);
						data.EventCallback(event);
						break;
					}
					break;
					default: ;
				}
			}
		);
		// 鼠标左键按下
		glfwSetMouseButtonCallback(m_Window,
			[](GLFWwindow* window, int button, int action, int modes)
			{
				WindowData data = *(WindowData*)glfwGetWindowUserPointer(window);
				switch (action)
				{
					case GLFW_PRESS :
					{
						MouseButtonPressedEvent event(button);
						data.EventCallback(event);
					}
					case GLFW_RELEASE:
					{
						MouseButtonReleasedEvent event(button);
						data.EventCallback(event);
					}
				default: ;
				}
			}
		);
		// 鼠标滚轮滚动
		glfwSetScrollCallback(m_Window, 
			[](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData data = *(WindowData*)glfwGetWindowUserPointer(window);
				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				data.EventCallback(event);
			}
		);
		// 当前鼠标位置
		glfwSetCursorPosCallback(m_Window,
			[](GLFWwindow* window, double xPos, double yPos)
			{
				WindowData data = *(WindowData*)glfwGetWindowUserPointer(window);
				MouseMovedEvent event((float)xPos, (float)yPos);
				data.EventCallback(event);
			}
		);
#pragma endregion

	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdata()
	{
		glfwPollEvents();
		// 刷新窗口
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
		{
			glfwSwapInterval(1);
		}
		else
		{
			glfwSwapInterval(0);
		}
		m_Data.VSync = enabled;
	}


	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}


}
