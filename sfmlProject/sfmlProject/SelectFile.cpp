#include "SelectFile.h"


std::string SelectFile::m_ListFilesInDir()
{
	return "NotImplemented";
}

SelectFile::SelectFile() : State()
{
	this->m_ImageDir = "unknown";
}


SelectFile::~SelectFile()
{
}

bool SelectFile::Init()
{
	return true;
}

int SelectFile::Update(sf::RenderWindow *window, bool signal)
{
	return 1;
}

bool SelectFile::Shutdown()
{
	return true;
}

std::string SelectFile::ToStringSpecific() const
{
	std::string ToReturn = "SELECT_FILE";
	return ToReturn;
}

std::string SelectFile::GetImageDir() const
{
	return this->m_ImageDir;
}
