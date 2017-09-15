#ifndef IMAGEALTERING_H
#define IMAGEALTERING_H

#include "State.h"
#include <stdlib.h>

class ImageAltering : public State
{
private:
	sf::Texture* m_toAlter;
	sf::Sprite* m_sprite;

	int** m_energyField;

	bool m_busy;

	int m_findRootPixel(const sf::Image &img);
	int m_nextPixel(int pixelX, int pixelY,const sf::Image &img);

	int width;

public:
	ImageAltering();
	virtual ~ImageAltering();

	bool Init();
	int Update(sf::RenderWindow *window);
	bool Shutdown();

	void FindNextSeam();
	void CarveStream();

	std::string ToStringSpecific() const;
};

#endif

