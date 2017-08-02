#ifndef STATE_H
#define STATE_H
#include <string>

#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"
#include "SFML\System.hpp"
#include "configFile.h"

class State
{
public:
	State();
	virtual ~State();

	virtual bool Init() = 0;
	virtual int Update(sf::RenderWindow *window, bool signal) = 0;
	virtual bool Shutdown() = 0;

	virtual std::string ToStringSpecific() const = 0;
	virtual std::string ToString() const;
};

#endif

