#ifndef READFILE_H
#define READFILE_H

#include "State.h"
class ReadFile : public State
{
public:
	ReadFile();
	virtual ~ReadFile();

	bool Init();
	int Update(sf::RenderWindow *window, bool signal);
	bool Shutdown();

	std::string ToStringSpecific() const;
};

#endif

