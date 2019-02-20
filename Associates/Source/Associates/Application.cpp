#include "Assoc_pch.h"

#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "Log.h"

namespace Associates
{
	Application::Application()
	{
	}


	Application::~Application()
	{

	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		ASSOC_TRACE(e);

		while (true)
		{

		}
	}
}
