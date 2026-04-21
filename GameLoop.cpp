#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;
using namespace sf;

int main()
{
	RenderWindow window(VideoMode(600, 600), "SnowBros", Style::Close);
	window.setFramerateLimit(60);

	if (!window.isOpen())
	{
		cout << "Couldn't Open Window" << endl;
		exit(-1);
	}

	View view({ 300, 300 }, { 600, 600 });

	while (window.isOpen())
	{
		window.setView(view);
		while (window.isOpen())
		{
			Event event;
			while (window.pollEvent(event))
			{				
				if (event.type == Event::Closed)
				{
					window.close();
				}
			}

			window.clear(Color::Cyan);


			window.display();
		}
	}

}