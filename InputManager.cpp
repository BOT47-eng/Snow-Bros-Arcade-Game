#include "InputManager.hpp"


void InputManager::setKeys(Keyboard::Scancode player1[4], Keyboard::Scancode player2[4])
{
	for (int i = 0; i < 4; i++)
	{
		player1Keys[i] = player1[i];
		player2Keys[i] = player2[i];
	}
}

//Called each cycle of game loop to reset movement
void InputManager::resetInput()
{
	player1Shot = false;
	player2Shot = false;
	player1Jumped = false;
	player2Jumped = false;
	gamePaused = false;
	debugHit = false;
}

//Movement does not use events and hence is smooth/continuous
bool InputManager::p1Left() const
{
	return Keyboard::isKeyPressed(player1Keys[0]);
}

bool InputManager::p2Left() const
{
	return Keyboard::isKeyPressed(player2Keys[0]);
}

bool InputManager::p1Right() const
{
	return Keyboard::isKeyPressed(player1Keys[1]);
}

bool InputManager::p2Right() const
{
	return Keyboard::isKeyPressed(player2Keys[1]);
}
	
//Getters for event checkers
bool InputManager::gamePause() const
{
	return gamePaused;
}

bool InputManager::debug() const
{
	return debugHit;
}

bool InputManager::p1Jump() const
{
	return player1Jumped;
}

bool InputManager::p2Jump() const
{
	return player2Jumped;
}

bool InputManager::p1Shoot() const
{
	return player1Shot;
}

bool InputManager::p2Shoot() const
{
	return player2Shot;
}

//Both jump and shoot uses events so they can only happen once per press
void InputManager::handleEvent(const Event& event)
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
