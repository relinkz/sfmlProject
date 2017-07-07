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

std::string SelectFile::GetImageDir() const
{
	return this->m_ImageDir;
}
