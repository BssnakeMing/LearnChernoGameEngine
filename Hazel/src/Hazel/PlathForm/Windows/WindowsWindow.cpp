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
			// ���glfw�Ƿ��ʼ���ɹ�
			HZ_CORE_ASSERT(success, "Could not intialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

		// ����һ��GLFW����
		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);

		// ��GLFW���������Զ����������Ϊ&����һ��void*, ���������κ�����
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

#pragma region ��GLFW���ڻص�����
		// ���ڴ�С�ı�
		glfwSetWindowSizeCallback(m_Window, 
			[](GLFWwindow* window, int width, int heigth)
			{
				// ��ȡ���ص��������Զ������
				WindowData data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.Width = width;
				data.Height = heigth;
				WindowResizeEvent event(width, heigth);
				data.EventCallback(event);
			}
		);
		// ���ڹر�
		glfwSetWindowCloseCallback(m_Window,
			[](GLFWwindow* window)
			{
				WindowData data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				data.EventCallback(event);
			}
		);
		// �����ڰ��¼�
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
					// �ü�һֱ����
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
		// ����������
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
		// �����ֹ���
		glfwSetScrollCallback(m_Window, 
			[](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData data = *(WindowData*)glfwGetWindowUserPointer(window);
				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				data.EventCallback(event);
			}
		);
		// ��ǰ���λ��
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
		// ˢ�´���
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
