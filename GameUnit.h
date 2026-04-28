#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "InputManager.h"
#include "Block.h"
#include "Player.h"
#include "PhysicsEngine.h"

class GameUnit {
public:
	static const float WIDTH;
	static const float HEIGHT;
private:
	RenderWindow window;
	bool isGameActive;
	bool levelMenu;
	bool leaderboard;
	bool loginMenu;

	//LoginManager manageLogin;
	//Leaderboard leaderboard;
	//Database manageSaves;
public:
	GameUnit() : isGameActive(false), levelMenu(false), leaderboard(false), loginMenu(false) 
	{
		window.create(VideoMode({ 600,600 }), "SnowBros 25I-3014 25I-3039", Style::Close);
		window.setFramerateLimit(60);
	}

	void launchGame();
	void drawLevel(int index);
	void drawMainMenu();
	void drawLeaderboard();
	void drawLoginMenu();
	void drawTesting();
}; 
