#pragma once

#ifdef ASSOC_PLATFORM_WINDOWS

extern Associates::Application* Associates::CreateApplication();

int main(int argc, char** argv)
{
	printf("Associates Engine\n");
	auto app = Associates::CreateApplication();
	app->Run();
	delete app;
}

#endif
