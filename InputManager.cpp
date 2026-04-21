#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class InputManager {
	private:
		bool player1Shot, player2Shot;
		bool player1Jumped, player2Jumped;
		bool gamePaused, debugHit;

		//0-left, 1-right, 2-up, 3-shoot
		Keyboard::Scancode player1Keys[4] = { Keyboard::Scancode::Left , Keyboard::Scancode::Right , Keyboard::Scancode::Space , Keyboard::Scancode::J };
		Keyboard::Scancode player2Keys[4] = { Keyboard::Scancode::A , Keyboard::Scancode::D , Keyboard::Scancode::W , Keyboard::Scancode::Space };

	public:
		void setKeys(Keyboard::Scancode player1[4], Keyboard::Scancode player2[4])
		{
			for (int i = 0; i < 4; i++)
			{
				player1Keys[i] = player1[i];
				player2Keys[i] = player2[i];
			}
		}

		//Called each cycle of game loop to reset movement
		void resetInput()
		{
			player1Shot = false;
			player2Shot = false;
			player1Jumped = false;
			player2Jumped = false;
			gamePaused = false;
			debugHit = false;
		}

		//Movement does not use events and hence is smooth/continuous
		bool p1Left()
		{
			return Keyboard::isKeyPressed(player1Keys[0]);
		}

		bool p2Left()
		{
			return Keyboard::isKeyPressed(player2Keys[0]);
		}

		bool p1Right()
		{
			return Keyboard::isKeyPressed(player1Keys[1]);
		}

		bool p2Right()
		{
			return Keyboard::isKeyPressed(player2Keys[1]);
		}

		//Both jump and shoot uses events so they can only happen once per press
		void handleEvent(const Event& event)
		{
			if (event.type == Event::KeyPressed)
			{
				if (event.key.scancode == player1Keys[2])
				{
					player1Jumped = true;
				}
				else if (event.key.scancode == player2Keys[2])
				{
					player2Jumped = true;
				}
				else if (event.key.scancode == player1Keys[3])
				{
					player1Shot = true;
				}
				else if (event.key.scancode == player2Keys[3])
				{
					player2Shot = true;
				}
			}
		}
};