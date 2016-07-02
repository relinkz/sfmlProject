#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"
#include "SFML\System.hpp"
#include "ImageProcessor.h"

//void sfmlCheck(); //call this if you want to check if smfl works

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	ImageProcessor ImgProcessor;

	try
	{
		ImgProcessor.initialize();
	}
	catch (char* errorMsg)
	{
		std::cout << errorMsg << std::endl;
	}

	std::cout << ImgProcessor.printColumn(0) << std::endl << "done";

	return 0;
}

void sfmlCheck()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}
}