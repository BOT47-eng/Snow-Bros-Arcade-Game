#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class InputManager {
	private:
		bool player1Shot, player2Shot;
		bool player1Jumped, player2Jumped;
	public:
		//Called each cycle of game loop to reset movement
		void resetInput()
		{
			player1Shot = false;
			player2Shot = false;
			player1Jumped = false;
			player2Jumped = false;
		}

		//Movement does not use events and hence is smooth/continuous
		bool p1Left()
		{
			return Keyboard::isKeyPressed(Keyboard::Scancode::Left);
		}

		bool p2Left()
		{
			return Keyboard::isKeyPressed(Keyboard::Scancode::A);
		}

		bool p1Right()
		{
			return Keyboard::isKeyPressed(Keyboard::Scancode::Right);
		}

		bool p2Right()
		{
			return Keyboard::isKeyPressed(Keyboard::Scancode::Left);
		}

		//Both jump and shoot uses events so they can only happen once per press
		void handleEvent(const Event& event)
		{
			if (event.type == Event::KeyPressed)
			{
				switch (event.key.scancode)
				{
					case Keyboard::Scancode::W:
						player1Jumped = true;
						break;
					case Keyboard::Scancode::Up:
						player2Jumped = true;
						break;
					case Keyboard::Scancode::J:
						player1Shot = true;
						break;
					case Keyboard::Scancode::Space:
						player2Shot = true;
						break;
				}
			}
		}
};