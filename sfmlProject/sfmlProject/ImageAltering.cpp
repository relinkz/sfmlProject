#include "ImageAltering.h"
#include <chrono>
#include <fstream>

int ImageAltering::m_findRootPixel(const sf::Image &img)
{
	int AvgEnergy = 0;
	int bestEnergy = 9999;
	

	int leastImportantPixel = 0;

	//find out the avarage colorvalue of the row
	for (int k = 0; k < img.getSize().x; k++)
	{
		AvgEnergy += img.getPixel(k, 0).r;
		AvgEnergy += img.getPixel(k, 0).g;
		AvgEnergy += img.getPixel(k, 0).b;

	}
	AvgEnergy /= (img.getSize().x * 3);

	for (int k = 0; k < img.getSize().x; k++)
	{
		int tempEnergy = 0;
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

	int k;
	int goal;
	
	if (pixelX == 0)
		k = 0;
	else
		k = -1;

	if (pixelX == img.getSize().x - 1)
	{
		goal = 1;
	}
	else
		goal = 2;

	for (int k = 0; k < img.getSize().x; k++)
	{
		AvgEnergy += img.getPixel(k, pixelY + 1).r;
		AvgEnergy += img.getPixel(k, pixelY + 1).g;
		AvgEnergy += img.getPixel(k, pixelY + 1).b;
	}
	AvgEnergy /= (this->width * 3);

	for (k; k < goal; k++)
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

void ImageAltering::m_initEnergyfield(const sf::Image &img)
{
	//image storing the energy of the pixel
	int avgEnergy[generalSettings::IMAGE_HEIGHT];

	int x_length = generalSettings::IMAGE_WIDTH - 1;
	int y_length = generalSettings::IMAGE_HEIGHT - 1;


	//find out the avarage colorvalue of the rows
	for (int i = 0; i < y_length; i++)
	{
		for (int k = 0; k < x_length; k++)
		{
			//get the average of the y column
			avgEnergy[i] += img.getPixel(k, i).r;
			avgEnergy[i] += img.getPixel(k, i).g;
			avgEnergy[i] += img.getPixel(k, i).b;
		}

		//avg
		avgEnergy[i] /= (img.getSize().x * 3);

		//the average energyvalue is now stored in avgEnergy for each row
		//The energy is determined by the following simple formula
		//energy = abs (avg(totColor) - avgColor)
		for (int k = 0; k < x_length; k++)
		{
			int energy = 0;

			//this are pointers, therfore dereference are needed
			energy += img.getPixel(k, i).r;
			energy += img.getPixel(k, i).g;
			energy += img.getPixel(k, i).b;

			//avg tot color
			energy /= 3;

			//abs(avgToTColor - rowAverage)
			energy = abs(energy - avgEnergy[i]);

			this->m_energyField[k][i] = energy;
		}

	}




}

void ImageAltering::m_initPowerfield()
{
	
}

ImageAltering::ImageAltering()
{
	this->m_toAlter = new sf::Texture();
	this->m_sprite = new sf::Sprite();
	
	this->m_busy = false;

	std::string filename = "C:/Users/Sebastian/Documents/GitHub/sfmlProject/sfmlProject/resources/green-sky.jpg";
	//std::string filename = "C:/Users/Sebastian/Documents/GitHub/sfmlProject/sfmlProject/resources/HJoceanSmall.png";

	this->m_toAlter->loadFromFile(filename);

	this->m_sprite->setTexture(*this->m_toAlter);
	this->width = this->m_toAlter->getSize().x - 1;

	//create energy and powerfield
	//energyfield holds every pixels energy
	//powerfield is used for finding out seams
	for (int i = 0; i < generalSettings::IMAGE_WIDTH; i++)
	{
		this->m_energyField[i] = new int[generalSettings::IMAGE_HEIGHT];
		this->m_powerField[i] = new int[generalSettings::IMAGE_HEIGHT];
	}
		
	//calculate each pixels energy
	sf::Image img = this->m_sprite->getTexture()->copyToImage();
	this->m_initEnergyfield(img);
	//initialize powerfield, find out each pixels energy
	//this->m_initPowerfield();



}

ImageAltering::~ImageAltering()
{
}

bool ImageAltering::Init()
{

	return true;
}

int ImageAltering::Update(sf::RenderWindow *window)
{
	//std::ofstream toFile;
	//toFile.open("exeTime.txt");
	//Update sends true as signal to move forward
	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();

			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::N)
				{
					this->FindNextSeam();
				}
				if (event.key.code == sf::Keyboard::C)
				{
					this->CarveStream();
				}
			}
		}

		window->clear();
		window->draw(*this->m_sprite);
		window->display();
	}
	//toFile.close();
	return 1;
}

bool ImageAltering::Shutdown()
{
	delete this->m_toAlter;
	delete this->m_sprite;

	for (int i = 0; i < generalSettings::IMAGE_WIDTH; i++)
	{
		delete[] this->m_energyField[i];
		delete[] this->m_powerField[i];
	}
	return true;
}

void ImageAltering::updatePowerfield()
{
	//first row

	//loop to bottom, it has to know their parent
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
		seam[i] = this->m_nextPixel(seam[i - 1], i - 1, img);
		img.setPixel(seam[i], i, redPix);
	}
	seam[sizeOfImage.y - 1] = this->m_nextPixel(seam[sizeOfImage.y - 2], sizeOfImage.y - 2, img);
	img.setPixel(seam[sizeOfImage.y - 1], sizeOfImage.y - 1, redPix);

	delete[] seam;
	this->m_toAlter->loadFromImage(img);
}

void ImageAltering::CarveStream()
{
	sf::Vector2u sizeOfImage = this->m_sprite->getTexture()->getSize();
	int* seam = new int[sizeOfImage.y];

	sf::Image img = this->m_sprite->getTexture()->copyToImage();
	sf::Color redPix = sf::Color::Red;

	//find the first pixel
	seam[0] = this->m_findRootPixel(img);

	//traverse from rootPix, creating the stream
	for (int i = 1; i < img.getSize().y - 1; i++)
		seam[i] = this->m_nextPixel(seam[i - 1], i, img);

	//remove stream, move all pixels back one step in array
	for (int k = 0; k < this->m_toAlter->getSize().y - 1; k++)
	{
		for (int i = seam[k]; i < this->width; i++)
			img.setPixel(i, k, img.getPixel(i + 1, k));
		img.setPixel(this->width, k, sf::Color::Black);
	}

	//for the last row
	seam[sizeOfImage.y - 1] = this->m_nextPixel(seam[sizeOfImage.y - 2], sizeOfImage.y - 2, img);
	for (int i = seam[sizeOfImage.y - 1]; i < this->m_toAlter->getSize().x- 1; i++)
		img.setPixel(i, sizeOfImage.y - 1, img.getPixel(i + 1, sizeOfImage.y - 1));

	img.setPixel(img.getSize().x - 1, sizeOfImage.y - 1, sf::Color::Black);
	delete[] seam;
	
	this->width--;
	this->m_toAlter->loadFromImage(img);
}

std::string ImageAltering::ToStringSpecific() const
{
	return std::string();
}
