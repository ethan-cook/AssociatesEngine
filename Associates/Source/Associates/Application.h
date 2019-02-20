#pragma once
#include "Core.h"

namespace Associates
{
	class ASSOC_API Application
	{
	public:
		Application();

		virtual	~Application();

		void Run();
	};

	Application* CreateApplication();
}

