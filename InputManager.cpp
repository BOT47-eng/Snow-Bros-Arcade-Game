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
		//P-Esc for pause and H-F1 for debug hitbox mode

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
		bool p1Left() const
		{
			return Keyboard::isKeyPressed(player1Keys[0]);
		}

		bool p2Left() const
		{
			return Keyboard::isKeyPressed(player2Keys[0]);
		}

		bool p1Right() const
		{
			return Keyboard::isKeyPressed(player1Keys[1]);
		}

		bool p2Right() const
		{
			return Keyboard::isKeyPressed(player2Keys[1]);
		}
	
		//Getters for event checkers
		bool gamePause() const
		{
			return gamePaused;
		}

		bool debug() const
		{
			return debugHit;
		}

		bool p1Jump() const
		{
			return player1Jumped;
		}

		bool p2Jump() const
		{
			return player2Jumped;
		}

		bool p1Shoot() const
		{
			return player1Shot;
		}

		bool p2Shoot() const
		{
			return player2Shot;
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
				else if (event.key.scancode == Keyboard::Scancode::P || event.key.scancode == Keyboard::Scancode::Escape)
				{
					gamePaused = true;
				}
				else if (event.key.scancode == Keyboard::Scancode::H || event.key.scancode == Keyboard::Scancode::F1)
				{
					debugHit = true;
				}
			}
		}
};