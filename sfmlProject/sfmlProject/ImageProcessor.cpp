#include "ImageProcessor.h"

bool ImageProcessor::initiateEnergyField()
{
	bool result = true;
	sf::Vector2u size;

	std::vector<int>temp;
	
	for (unsigned int i = 0; i < size.x; i++)
	{
		temp.push_back(0);
	}
	for (unsigned int i = 0; i < size.y; i++)
	{
		this->energyField.push_back(temp);
	}
	return result;
}

bool ImageProcessor::calculateEnergyValue()
{
	
}

ImageProcessor::ImageProcessor()
{
}

ImageProcessor::~ImageProcessor()
{
}

void ImageProcessor::initialize(const std::string & fileSrc) throw(...)
{
	bool result = true;
	std::string srcPath = "C:/Users/Sebastian/Documents/GitHub/sfmlProject/sfmlProject/resources/"+fileSrc;

	result = this->srcImage.loadFromFile(srcPath);
	
	if (result == true)
	{
		result = initiateEnergyField();
		if (result == false)
		{
			throw("failed to create the energyField");
		}
	}
	else
	{
		throw("srcImage.loadFromFile in ImageProcessor error");
	}
}
