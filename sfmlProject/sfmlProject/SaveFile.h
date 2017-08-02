#ifndef SAVEFILE_H
#define SAVEFILE_H

#include "State.h"
class SaveFile : public State
{
public:
	SaveFile();
	virtual ~SaveFile();

	bool Init();
	int Update(sf::RenderWindow *window);
	bool Shutdown();

	std::string ToStringSpecific() const;
};

#endif
