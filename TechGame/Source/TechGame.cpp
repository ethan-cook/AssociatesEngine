#include <Associates.h>

class ExampleLayer : public Associates::Layer
{
public:
	ExampleLayer() : Layer("Example")
	{

	}

	void OnUpdate() override
	{
		ASSOC_INFO("ExampleLayer::Update");
	}

	void OnEvent(Associates::Event& Event) override
	{
		ASSOC_INFO("{0}", Event);
	}
};


class TechGame : public Associates::Application
{
public:

	TechGame()
	{
		PushLayer(new ExampleLayer());
	}

	~TechGame()
	{

	}
};

Associates::Application* Associates::CreateApplication()
{
	return new TechGame();
}