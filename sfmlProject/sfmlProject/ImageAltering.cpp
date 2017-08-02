#include "ImageAltering.h"

ImageAltering::ImageAltering()
{
	this->m_toAlter = new sf::Texture();
	this->m_sprite = new sf::Sprite();
	
	std::string filename = "C:/Users/Sebastian/Documents/GitHub/sfmlProject/sfmlProject/resources/green-sky.jpg";
	
	sf::Vector2i ImageSize(generalSettings::IMAGE_WIDTH, generalSettings::IMAGE_HEIGHT);
	if (!this->m_toAlter->loadFromFile(filename, sf::IntRect(sf::Vector2i(0, 0), ImageSize)))
	{
		int i = 0;
		i + 5;
	}

	this->m_sprite->setTexture(*this->m_toAlter);

}


ImageAltering::~ImageAltering()
{
}

bool ImageAltering::Init()
{
	return false;
}

int ImageAltering::Update(sf::RenderWindow *window)
{
	window->draw(*this->m_sprite);
	return 0;
}

bool ImageAltering::Shutdown()
{
	delete this->m_toAlter;
	delete this->m_sprite;

	return true;
}

std::string ImageAltering::ToStringSpecific() const
{
	return std::string();
}
