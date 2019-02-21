#include "Assoc_pch.h"
#include "WindowsWindow.h"

#include "Associates/Events/ApplicationEvent.h"
#include "Associates/Events/MouseEvent.h"
#include "Associates/Events/KeyEvent.h"

#include <glad/glad.h>

namespace Associates
{
	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int Error, const char* Description)
	{
		ASSOC_CORE_ERROR("GLFW Error ({0}): {1}", Error, Description);
	}

	Window* Window::Create(const WindowProps& Props)
	{
		return new WindowsWindow(Props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& Props)
	{
		Init(Props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& Props)
	{
		m_Data.Title = Props.Title;
		m_Data.Width = Props.Width;
		m_Data.Height = Props.Height;

		ASSOC_CORE_INFO("Creating Window {0} ({1}, {2})", Props.Title, Props.Width, Props.Height);

		if (!s_GLFWInitialized)
		{
			int Success = glfwInit();
			ASSOC_CORE_ASSERT(Success, "Could not initialized GLFW!");

			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)m_Data.Width, (int)m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);

		int Status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		ASSOC_CORE_ASSERT(Status, "Failed to intialize glad!");

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		//Set GLFW Callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* Window, int Width, int Height)
		{
			WindowData& Data = *(WindowData*)glfwGetWindowUserPointer(Window);
			Data.Width = Width;
			Data.Height = Height;

			WindowResizeEvent Event(Width, Height);
			Data.EventCallback(Event);		
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* Window)
		{
			WindowData& Data = *(WindowData*)glfwGetWindowUserPointer(Window);
			WindowCloseEvent Event;
			Data.EventCallback(Event);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* Window, int Key, int Scancode, int Action, int Mods)
		{
			WindowData& Data = *(WindowData*)glfwGetWindowUserPointer(Window);
			
			switch (Action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent Event(Key, 0);
					Data.EventCallback(Event);
					break;
				}

				case GLFW_RELEASE:
				{
					KeyReleasedEvent Event(Key);
					Data.EventCallback(Event);
					break;
				}

				case GLFW_REPEAT:
				{
					KeyPressedEvent Event(Key, 1);
					Data.EventCallback(Event);
					break;
				}

				default:
					break;
			}
		});

		glfwSetCharCallback(m_Window, [](GLFWwindow* Window, unsigned int KeyCode)
		{
			WindowData& Data = *(WindowData*)glfwGetWindowUserPointer(Window);

			KeyTypedEvent Event(KeyCode);
			Data.EventCallback(Event);
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* Window, int Button, int Action, int Mods)
		{
			WindowData& Data = *(WindowData*)glfwGetWindowUserPointer(Window);

			switch (Action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent Event(Button);
					Data.EventCallback(Event);
					break;
				}

				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent Event(Button);
					Data.EventCallback(Event);
					break;
				}

				default:
					break;
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* Window, double xOffset, double yOffset)
		{
			WindowData& Data = *(WindowData*)glfwGetWindowUserPointer(Window);

			MouseScrolledEvent Event((float)xOffset, (float)yOffset);
			Data.EventCallback(Event);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* Window, double xPos, double yPos)
		{
			WindowData& Data = *(WindowData*)glfwGetWindowUserPointer(Window);

			MouseMovedEvent Event((float)xPos, (float)yPos);
			Data.EventCallback(Event);
		});

	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::SetVSync(bool bEnabled)
	{
		if (bEnabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.bVSync = bEnabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.bVSync;
	}
}
