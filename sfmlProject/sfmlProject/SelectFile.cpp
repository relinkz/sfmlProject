#include "SelectFile.h"


SelectFile::SelectFile() : State()
{
}


SelectFile::~SelectFile()
{
}

bool SelectFile::Init()
{
	return true;
}

bool SelectFile::Update()
{
	return true;
}

bool SelectFile::Shutdown()
{
	return true;
}

std::string SelectFile::ToStringSpecific() const
{
	std::string ToReturn = "Empty SelectFile String";
	return ToReturn;
}
