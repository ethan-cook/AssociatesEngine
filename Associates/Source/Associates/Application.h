#pragma once
#include "Core.h"

#include "LayerStack.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"

#include "Window.h"

namespace Associates
{
	class ASSOC_API Application
	{
	public:
		Application();

		virtual	~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);

		void PushOverlay(Layer* Overlay);

	private:

		bool OnWindowClose(WindowCloseEvent& e);
		
		std::unique_ptr<Window> m_Window;

		bool m_bRunning = true;

		LayerStack m_LayerStack;
	};

	//To be defined in Client
	Application* CreateApplication();
}

