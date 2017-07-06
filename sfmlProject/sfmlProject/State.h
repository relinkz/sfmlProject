#ifndef STATE_H
#define STATE_H
#include <string>

class State
{
public:
	State();
	virtual ~State();

	virtual bool Init();
	virtual bool Update();
	virtual bool Shutdown();

	virtual std::string ToStringSpecific() const = 0;
	virtual std::string ToString() const;
};

#endif

