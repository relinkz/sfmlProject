#include "Engine.h"

Engine::Engine()
{
	this->m_activeState = -1;
	for (int i = 0; i < coreSettings::NR_OF_STATES; i++)
	{
		this->m_states[i] = nullptr;
	}

	this->m_window = nullptr;
}


Engine::~Engine()
{
}

void Engine::Init()
{
	//selectFile state is the first to execute
	this->m_activeState = 2;

	this->m_states[0] = new SelectFile();
	this->m_states[1] = new ReadFile();
	this->m_states[2] = new ImageAltering();
	this->m_states[3] = new SaveFile();

	this->m_window = new sf::RenderWindow(sf::VideoMode(generalSettings::IMAGE_WIDTH, generalSettings::IMAGE_HEIGHT), "Seamcarver");
}

void Engine::Run()
{
	//Update sends true as signal to move forward
	if (this->m_states[this->m_activeState]->Update(this->m_window) == true)
	{
		while (this->m_window->isOpen())
		{
			sf::Event event;
			while (this->m_window->pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					this->m_window->close();
			}

			this->m_window->clear();
			this->m_states[this->m_activeState]->Update(this->m_window);
			this->m_window->display();
		}

	}
}

void Engine::Shutdown()
{
	for (int i = 0; i < coreSettings::NR_OF_STATES; i++)
	{
		this->m_states[i]->Shutdown();
		delete this->m_states[i];
	}
	delete this->m_window;

}
