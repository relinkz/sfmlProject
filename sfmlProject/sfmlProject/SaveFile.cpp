#include "SaveFile.h"



SaveFile::SaveFile()
{
}


SaveFile::~SaveFile()
{
}

bool SaveFile::Init()
{
	return false;
}

int SaveFile::Update(sf::RenderWindow *window, bool signal)
{
	return 1;
}

bool SaveFile::Shutdown()
{
	return false;
}

std::string SaveFile::ToStringSpecific() const
{
	return std::string();
}
