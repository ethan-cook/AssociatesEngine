#include <Associates.h>

class TechGame : public Associates::Application
{
public:
	TechGame()
	{

	}

	~TechGame()
	{

	}
};

Associates::Application* Associates::CreateApplication()
{
	return new TechGame();
}