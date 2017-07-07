#ifndef SELECTFILE
#define SELECTFILE

#include "State.h"

/*
The purpuse of this class is to secure that the image from the working directory (m_Imgdirr)
exist and make every thing ready for the next state, ReadFile.
*/

class SelectFile : public State
{
private:
	std::string m_ImageDir;

private:
	std::string m_ListFilesInDir();

public:
	SelectFile();
	virtual ~SelectFile();

	bool Init();
	bool Update();
	bool Shutdown();

	std::string ToStringSpecific() const;
	std::string GetImageDir() const;
};

#endif
