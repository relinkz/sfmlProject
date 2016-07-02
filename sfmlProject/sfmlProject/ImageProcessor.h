#ifndef IMAGEPROCESSOR
#define IMAGEPROCESSOR

#include "SFML\Graphics.hpp"
#include <vector>
#include <list>
#include <string>
#include <sstream>
#include <iostream>

class ImageProcessor
{
	
private:
	static int const MAX_PARENTS = 3;
	//useful structs
	struct Pixel
	{
		int red;
		int green;
		int blue;
	};
	//struct for calculating the energy values
	struct PixelChunk
	{
		Pixel parents[MAX_PARENTS]; //3
		Pixel active;
	};
	//struct for holding th energy values
	struct EnergyNode
	{
		float parents[MAX_PARENTS]; //3
		float active;
	};
private:
	sf::Image srcImage;
	std::vector<std::vector<int>>energyField;

	bool initiateEnergyField();
	bool calculateEnergyValue();
	
	
	//findSeam();
public:
	ImageProcessor();
	virtual ~ImageProcessor();

	void initialize(const std::string & fileSrc = "HJoceanSmall.png") throw(...);
	std::string printColumn(const int &columnNr);
};

#endif