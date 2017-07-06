#ifndef STATE_H
#define STATE_H
#include <string>

class State
{
public:
	State();
	virtual ~State();

	virtual bool Init() = 0;
	virtual bool Update() = 0;
	virtual bool Shutdown() = 0;

	virtual std::string ToStringSpecific() const = 0;
	virtual std::string ToString() const;
};

#endif

