#ifndef IMAGEALTERING_H
#define IMAGEALTERING_H

#include "State.h"
#include <stdlib.h>


class ImageAltering : public State
{
private:
	sf::Texture* m_toAlter;
	sf::Sprite* m_sprite;

	sf::Image* m_picture;
	sf::Image* m_energyPicture;

	bool m_showEnergy;

	int* m_energyField[generalSettings::IMAGE_WIDTH];
	void ImageAltering::m_printEnergyPathToFile() const;

	bool m_busy;

	int m_findRootPixel(const sf::Image &img);
	int m_nextPixel(int pixelX, int pixelY,const sf::Image &img);
	
	void m_initEnergyPicture(const sf::Image &img);

	void m_energyMapUpdate();


	int width;

public:
	ImageAltering();
	virtual ~ImageAltering();

	bool Init();
	int Update(sf::RenderWindow *window);
	bool Shutdown();

	void updatePowerfield();

	void FindNextSeam();
	void CarveStream();

	std::string ToStringSpecific() const;
};

#endif

