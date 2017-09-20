#include "ImageAltering.h"
#include <chrono>
#include <fstream>

void ImageAltering::m_printEnergyPathToFile() const
{
	std::ofstream toFile;
	toFile.open("EnergyField.txt");

	std::string toReturn = "";
	for (int i = 0; i < generalSettings::IMAGE_HEIGHT - 1; i++)
	{
		for (int k = 0; k < generalSettings::IMAGE_WIDTH - 1; k++)
		{
			toReturn += "[" + std::to_string(this->m_energyField[k][i]) + "]";
		}
		toReturn += "\n";
	}

	toFile << toReturn;
	toFile.close();
}

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

void ImageAltering::m_initEnergyPicture(const sf::Image &img)
{
	//image storing the energy of the pixel
	int avgEnergy[generalSettings::IMAGE_HEIGHT];

	int x_length = generalSettings::IMAGE_WIDTH;
	int y_length = generalSettings::IMAGE_HEIGHT;

	//get image from texture
	sf::Image copy = this->m_sprite->getTexture()->copyToImage();

	//find out the avarage colorvalue of the rows
	for (int i = 0; i < y_length; i++)
	{
		for (int k = 0; k < x_length; k++)
		{
			avgEnergy[i] = 0;
			//get the average of the y column
			avgEnergy[i] += img.getPixel(k, i).r;
			avgEnergy[i] += img.getPixel(k, i).g;
			avgEnergy[i] += img.getPixel(k, i).b;

			avgEnergy[i] /= 3;
		}

		//avg
		avgEnergy[i] /= (img.getSize().x);

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
			
			sf::Color pix = sf::Color(energy, energy, energy);
			copy.setPixel(k,i,pix);
		}
	}
	this->m_energyPicture = new sf::Image(copy);
}

void ImageAltering::m_energyMapUpdate()
{
	int length_x = this->width;
	//int length_x = this->width;

	int length_y = generalSettings::IMAGE_HEIGHT;

	for (int i = 1; i < length_y; i++)
	{
		for (int k = 0; k < length_x; k++)
		{
			//first in row
			if (k == 0)
			{
				int lowest = 0;
				int temp = 0;
				//check above
				lowest = this->m_energyField[k][i - 1];
				//check above right
				temp = this->m_energyField[k + 1][i - 1];

				//make sure lowest energy is saved
				if (lowest > temp)
					lowest = temp;

				//add to value
				this->m_energyField[k][i] += lowest;


			}

			else if (k == (length_x - 1))
			{
				int lowest = 0;
				int temp = 0;

				//pixel above
				lowest = this->m_energyField[k][i - 1];

				temp = this->m_energyField[k - 1][i - 1];

				if (lowest > temp)
					lowest = temp;
				
				this->m_energyField[k][i] += lowest;
			}

			else
			{
				int lowest = 0;
				int temp = 0;

				//top left
				lowest = this->m_energyField[k - 1][i - 1];
				
				//top
				temp = this->m_energyField[k][i - 1];

				//make sure lowest has less enery of the first 2
				if (lowest > temp)
					lowest = temp;

				//get the right pixel
				temp = this->m_energyField[k + 1][i - 1];

				//save the lowest value
				if(lowest > temp)
					lowest = temp;

				this->m_energyField[k][i] += lowest;
			}
		}
	}
}

ImageAltering::ImageAltering()
{
	this->m_toAlter = new sf::Texture();
	this->m_sprite = new sf::Sprite();
	
	this->m_busy = false;

	std::string filename = "C:/Users/Sebastian/Documents/GitHub/sfmlProject/sfmlProject/resources/green-sky.jpg";
	//std::string filename = "C:/Users/Sebastian/Documents/GitHub/sfmlProject/sfmlProject/resources/HJoceanSmall.png";

	this->m_toAlter->loadFromFile(filename);

	this->m_picture = nullptr;
	this->m_energyPicture = nullptr;

	this->m_picture = new sf::Image(this->m_toAlter->copyToImage());

	this->m_sprite->setTexture(*this->m_toAlter);
	this->width = this->m_toAlter->getSize().x - 1;

	this->m_showEnergy = false;
}

ImageAltering::~ImageAltering()
{
}

bool ImageAltering::Init()
{
	//ällocate memory for energy and powerfield
	
	//energyfield holds every pixels energy
	//powerfield is used for finding out seams
	for (int i = 0; i < generalSettings::IMAGE_WIDTH; i++)
	{
		this->m_energyField[i] = new int[generalSettings::IMAGE_HEIGHT];
	}

	//calculate each pixels energy
	sf::Image img = this->m_sprite->getTexture()->copyToImage();
	this->m_initEnergyPicture(img);
	
	//initialize powerfield, find out each pixels energy
	//this->m_initPowerfield();
	return true;
}

int ImageAltering::Update(sf::RenderWindow *window)
{
	this->width = generalSettings::IMAGE_WIDTH - 1;
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
					////swap state
					this->m_showEnergy = !this->m_showEnergy;

					if (this->m_showEnergy == true)
						this->m_toAlter->loadFromImage(*this->m_energyPicture);
					else
						this->m_toAlter->loadFromImage(*this->m_picture);

					//this->m_printEnergyPathToFile();
					//printf("%s", "done");
				}
				if (event.key.code == sf::Keyboard::C)
				{
					//this->CarveStream();
					
					this->m_energyMapUpdate();
					//this->m_printEnergyPathToFile();
					this->FindNextSeam();
					this->width--;

					printf("%s", "done");
					
					
					//this->FindNextSeam();
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
	}

	if (this->m_picture != nullptr)
	{
		delete this->m_picture;
		this->m_picture = nullptr;
	}

	if (this->m_energyPicture != nullptr)
	{
		delete this->m_energyPicture;
		this->m_energyPicture = nullptr;
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
	int length_y = generalSettings::IMAGE_HEIGHT - 1;
	int length_x = this->width - 1;


	sf::Image img = this->m_sprite->getTexture()->copyToImage();
	sf::Color redPix = sf::Color::Red;

	int lowestVal = 0;
	int temp;
	int pos[generalSettings::IMAGE_HEIGHT];

	lowestVal = this->m_energyField[0][length_y];
	pos[0] = 0;

	for (int i = 1; i < length_x + 1; i++)
	{
		temp = this->m_energyField[i][length_y];
		if (lowestVal > temp)
		{
			lowestVal = temp;
			pos[0] = i;
		}
	}

	for (int i = 1; i < length_y + 1; i++)
	{
		if (pos[i - 1] == 0)
		{
			int prev = pos[i - 1];
			//top left
			int lowest = this->m_energyField[prev][length_y - i];
			//wild guess that the top pixel is least important
			pos[i] = prev;

			//top
			int temp = this->m_energyField[prev + 1][length_y - i];

			if (lowest > temp)
			{
				lowest = temp;

				//just above, that is same x value
				pos[i] = prev + 1;
			}
		}

		else if (pos[i - 1] == length_x)
		{
			int prev = pos[i - 1];
			//top left
			int lowest = this->m_energyField[prev - 1][length_y - i];
			//wild guess that the top left pixel is least important
			pos[i] = prev - 1;

			//top
			int temp = this->m_energyField[prev][length_y - i];

			if (lowest > temp)
			{
				lowest = temp;

				//just above, that is same x value
				pos[i] = prev;
			}
		}
	
		else
		{
			int prev = pos[i - 1];
			//top left
			int lowest = this->m_energyField[prev - 1][length_y - i];
			//wild guess that the top left pixel is least important
			pos[i] = prev - 1;

			//top
			int temp = this->m_energyField[prev][length_y - i];

			if (lowest > temp)
			{
				lowest = temp;

				//just above, that is same x value
				pos[i] = prev;
			}

			temp = this->m_energyField[prev + 1][length_y - i];

			if (lowest > temp)
			{
				lowest = temp;

				//same pos but top right
				pos[i] = prev + 1;
			}
			sf::Vector2i pixelPos = sf::Vector2i(pos[i], (length_y - i));
			img.setPixel(pos[i], (length_y - i), redPix);
		}
	}

	delete this->m_energyPicture;
	this->m_energyPicture = new sf::Image(img);

	//remove the seam
	for (int k = 0; k < this->m_toAlter->getSize().y - 1; k++)
	{
		for (int i = pos[k]; i < this->width; i++)
			img.setPixel(i, length_y - k, img.getPixel(i + 1, length_y - k));
		img.setPixel(this->width, k, sf::Color::Black);
	}

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
