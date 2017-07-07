#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"
#include "SFML\System.hpp"
#include "SelectFile.h"
#include <boost/lambda/lambda.hpp>
#include <cstdio>
#include <iostream>
#include <iterator>
#include <algorithm>


int main()
{

	/* Checking boost lib
	using namespace boost::lambda;

	typedef std::istream_iterator<int> in;

	std::for_each(
		in(std::cin), in(), std::cout << (_1 * 3) << " ");
		*/

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	State* state = nullptr;
	state = new SelectFile;

	printf(state->ToString().c_str());

	//sebImageProcessor are the FSM, controlling the states

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

	return 0;
}