#ifndef IMAGEALTERING_H
#define IMAGEALTERING_H

#include "State.h"
#include <stdlib.h>

class ImageAltering : public State
{
private:
	sf::Texture* m_toAlter;
	sf::Sprite* m_sprite;

	bool m_busy;

	int m_findRootPixel(const sf::Image &img);
	int m_nextPixel(int pixelX, int pixelY,const sf::Image &img);

public:
	ImageAltering();
	virtual ~ImageAltering();

	bool Init();
	int Update(sf::RenderWindow *window, bool signal);
	bool Shutdown();

	void FindNextSeam();

	std::string ToStringSpecific() const;
};

#endif

