#ifndef ENGINE
#define ENGINE

#include "configFile.h"
#include "SelectFile.h"
#include "ReadFile.h"
#include "ImageAltering.h"
#include "SaveFile.h"

class Engine
{
private:
	int m_activeState;
	State* m_states[coreSettings::NR_OF_STATES];

	sf::RenderWindow* m_window;
public:
	Engine();
	virtual ~Engine();

	void Init();
	void Run();
	void Shutdown();
};

#endif
