#pragma once

#include "Associates/Window.h"
#include <GLFW/glfw3.h>

namespace Associates
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& Props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		//Window attributes
		inline void SetEventCallback(const EventCallbackFn& Callback) override { m_Data.EventCallback = Callback; }
		void SetVSync(bool bEnabled) override;
		bool IsVSync() const override;

	private:
		virtual void Init(const WindowProps& Props);
		virtual void Shutdown();

		GLFWwindow* m_Window;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool bVSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};
}

