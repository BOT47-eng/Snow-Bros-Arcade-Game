#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class InputManager {
private:
	bool player1Shot, player2Shot;
	bool player1Jumped, player2Jumped;
	bool gamePaused, debugHit;

	//0-left, 1-right, 2-up, 3-shoot
	sf::Keyboard::Scancode player1Keys[4] = { sf::Keyboard::Scancode::Left , sf::Keyboard::Scancode::Right , sf::Keyboard::Scancode::Up , sf::Keyboard::Scancode::J };
	sf::Keyboard::Scancode player2Keys[4] = { sf::Keyboard::Scancode::A , sf::Keyboard::Scancode::D , sf::Keyboard::Scancode::W , sf::Keyboard::Scancode::Space };
	//P-Esc for pause and H-F1 for debug hitbox mode

public:
	void setKeys(sf::Keyboard::Scancode player1[4], sf::Keyboard::Scancode player2[4]);

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
	void handleEvent(const sf::Event& event);

};