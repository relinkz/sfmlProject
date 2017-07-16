#include "State.h"

State::State()
{

}

State::~State()
{

}

std::string State::ToString() const
{
	std::string ToReturn = "STATE: ";

	ToReturn.append(" " + this->ToStringSpecific());

	return ToReturn;
}
