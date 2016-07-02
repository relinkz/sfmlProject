#include "ImageProcessor.h"

bool ImageProcessor::initiateEnergyField()
{
	bool result = true;
	sf::Vector2u size;

	//get the image size, width and height
	size = this->srcImage.getSize();

	//create a temporary vector 
	std::vector<int>temp;
	for (unsigned int i = 0; i < size.x; i++)
	{
		temp.push_back(0);
	}
	//let the energy field store that vector, copy of it
	//this will keep store of the texels "energy"
	for (unsigned int i = 0; i < size.y; i++)
	{
		this->energyField.push_back(temp);
	}
	return result;
}

bool ImageProcessor::calculateEnergyValue()
{
	return true;
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

std::string ImageProcessor::printColumn(const int & columnNr)
{
	std::stringstream toString;
	sf::Vector2u size = this->srcImage.getSize();

	if (size.x < columnNr)
	{
		toString << "column number out of range!" << std::endl;
	}
	else
	{
		toString << "column :" << columnNr << ": ";
		for (int i = 0; i < size.y; i++)
		{
			toString << this->energyField.at(columnNr).at(i);
		}
		toString << std::endl;
	}
	return toString.str();
}
