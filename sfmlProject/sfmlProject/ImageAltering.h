#ifndef IMAGEALTERING_H
#define IMAGEALTERING_H

#include "State.h"

class ImageAltering : public State
{
private:
	sf::Texture* m_toAlter;
	sf::Color* m_rawImage;
	sf::Sprite* m_sprite;

public:
	ImageAltering();
	virtual ~ImageAltering();

	bool Init();
	int Update(sf::RenderWindow *window);
	bool Shutdown();

	std::string ToStringSpecific() const;
};

#endif

