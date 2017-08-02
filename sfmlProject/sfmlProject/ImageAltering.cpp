#include "ImageAltering.h"

int ImageAltering::m_findRootPixel(const sf::Image &img)
{
	int AvgEnergy = 0;
	int bestEnergy = 9999;
	int tempEnergy = 0;

	int leastImportantPixel = 0;

	//find out the avarage colorvalue of the row
	for (int k = 0; k < generalSettings::IMAGE_WIDTH; k++)
	{
		AvgEnergy += img.getPixel(k, 0).r;
		AvgEnergy += img.getPixel(k, 0).g;
		AvgEnergy += img.getPixel(k, 0).b;

	}
	AvgEnergy /= (generalSettings::IMAGE_WIDTH * 3);

	for (int k = 0; k < generalSettings::IMAGE_WIDTH; k++)
	{
		tempEnergy += abs(AvgEnergy - img.getPixel(k, 0).r);
		tempEnergy += abs(AvgEnergy - img.getPixel(k, 0).g);
		tempEnergy += abs(AvgEnergy - img.getPixel(k, 0).b);

		//if best, save it
		if (tempEnergy < bestEnergy)
		{
			bestEnergy = tempEnergy;
			leastImportantPixel = k;
		}
	}
	return leastImportantPixel;
}

int ImageAltering::m_nextPixel(int pixelX, int pixelY,const sf::Image & img)
{
	int leastImportantPixel = 0;
	int bestEnergy = 9999;
	int AvgEnergy = 0;

	for (int k = 0; k < img.getSize().x; k++)
	{
		AvgEnergy += img.getPixel(k, pixelY + 1).r;
		AvgEnergy += img.getPixel(k, pixelY + 1).g;
		AvgEnergy += img.getPixel(k, pixelY + 1).b;

	}
	AvgEnergy /= (generalSettings::IMAGE_WIDTH * 3);

	for (int k = -1; k < 2; k++)
	{
		int tempEnergy = 0;

		tempEnergy += abs(AvgEnergy - img.getPixel(pixelX + k, pixelY + 1).r);
		tempEnergy += abs(AvgEnergy - img.getPixel(pixelX + k, pixelY + 1).g);
		tempEnergy += abs(AvgEnergy - img.getPixel(pixelX + k, pixelY + 1).b);

		//if best, save it
		if (tempEnergy < bestEnergy)
		{
			bestEnergy = tempEnergy;
			leastImportantPixel = pixelX + k;
		}
	}
	return leastImportantPixel;
}

ImageAltering::ImageAltering()
{
	this->m_toAlter = new sf::Texture();
	this->m_sprite = new sf::Sprite();
	
	this->m_busy = false;

	std::string filename = "C:/Users/Sebastian/Documents/GitHub/sfmlProject/sfmlProject/resources/green-sky.jpg";
	
	sf::Vector2i ImageSize(generalSettings::IMAGE_WIDTH, generalSettings::IMAGE_HEIGHT);
	this->m_toAlter->loadFromFile(filename, sf::IntRect(sf::Vector2i(0, 0), ImageSize));

	this->m_sprite->setTexture(*this->m_toAlter);
}


ImageAltering::~ImageAltering()
{
}

bool ImageAltering::Init()
{
	return false;
}

int ImageAltering::Update(sf::RenderWindow *window, bool signal)
{
	window->draw(*this->m_sprite);
	if (this->m_busy == false && signal == true)
	{
		this->m_busy = true;
		this->FindNextSeam();
	}
	return 1;
}

bool ImageAltering::Shutdown()
{
	delete this->m_toAlter;
	delete this->m_sprite;

	return true;
}

void ImageAltering::FindNextSeam()
{
	sf::Vector2u sizeOfImage = this->m_sprite->getTexture()->getSize();
	int* seam = new int[sizeOfImage.y];
	
	sf::Image img = this->m_sprite->getTexture()->copyToImage();
	sf::Color redPix = sf::Color::Red;

	int leastImportantPixel = 0;
	
	
	seam[0] = this->m_findRootPixel(img);

	img.setPixel(seam[0], 0, redPix);

	//traverse from rootPix
	for (int i = 1; i < img.getSize().y - 1; i++)
	{
		seam[i] = this->m_nextPixel(seam[i - 1], i, img);
		img.setPixel(seam[i], i, redPix);
	}

	//color stream red
	//img.setPixel(rootPix, 0, redPix);

	sf::Vector2i ImageSize(generalSettings::IMAGE_WIDTH, generalSettings::IMAGE_HEIGHT);
	sf::IntRect rect = sf::IntRect(sf::Vector2i(0, 0), ImageSize);

	this->m_toAlter->loadFromImage(img, rect);
}

std::string ImageAltering::ToStringSpecific() const
{
	return std::string();
}
