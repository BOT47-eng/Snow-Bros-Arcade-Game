#pragma once
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
	Keyboard::Scancode player1Keys[4] = { Keyboard::Scancode::Left , Keyboard::Scancode::Right , Keyboard::Scancode::Up , Keyboard::Scancode::J };
	Keyboard::Scancode player2Keys[4] = { Keyboard::Scancode::A , Keyboard::Scancode::D , Keyboard::Scancode::W , Keyboard::Scancode::Space };
	//P-Esc for pause and H-F1 for debug hitbox mode

public:
	void setKeys(Keyboard::Scancode player1[4], Keyboard::Scancode player2[4]);

	//Called each cycle of game loop to reset movement
	void resetInput();

	//Movement does not use events and hence is smooth/continuous
	bool p1Left() const;

	bool p2Left() const;

	bool p1Right() const;

	bool p2Right() const;

	//Getters for event checkers
	bool gamePause() const;

	bool debug() const;

	bool p1Jump() const;

	bool p2Jump() const;

	bool p1Shoot() const;

	bool p2Shoot() const;

	//Both jump and shoot uses events so they can only happen once per press
	void handleEvent(const Event& event);

};