#pragma once

#ifdef ASSOC_PLATFORM_WINDOWS

extern Associates::Application* Associates::CreateApplication();

int main(int argc, char** argv)
{
	Associates::Log::Init();
	ASSOC_CORE_WARN("Initialized Log!");
	int a = 5;
	ASSOC_INFO("Hello! Var={0}", a);

	printf("Associates Engine\n");
	auto app = Associates::CreateApplication();
	app->Run();
	delete app;
}

#endif
