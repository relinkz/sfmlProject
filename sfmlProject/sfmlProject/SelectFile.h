#ifndef SELECTFILE
#define SELECTFILE

#include "State.h"

class SelectFile : public State
{
public:
	SelectFile();
	virtual ~SelectFile();

	bool Init();
	bool Update();
	bool Shutdown();

	std::string ToStringSpecific() const;
};

#endif
