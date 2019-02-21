#include <Associates.h>

class ExampleLayer : public Associates::Layer
{
public:
	ExampleLayer() : Layer("Example")
	{

	}

	void OnUpdate() override
	{
		//ASSOC_INFO("ExampleLayer::Update");

		if (Associates::Input::IsKeyPressed(ASSOC_KEY_TAB))
			ASSOC_TRACE("Tab key is pressed!");
	}

	void OnEvent(Associates::Event& Event) override
	{
		//ASSOC_INFO("{0}", Event);
	}
};


class TechGame : public Associates::Application
{
public:

	TechGame()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Associates::ImGUILayer());
	}

	~TechGame()
	{

	}
};

Associates::Application* Associates::CreateApplication()
{
	return new TechGame();
}