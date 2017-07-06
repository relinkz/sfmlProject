#include "State.h"

State::State()
{

}

State::~State()
{

}

std::string State::ToString() const
{
	std::string ToReturn = "Empty";

	ToReturn.append(" " + this->ToStringSpecific());

	return ToReturn;
}
