#pragma once
#include <SFML/Graphics.hpp>
#include <string>

#include "InputManager.hpp"
#include "Block.hpp"
#include "Player.hpp"
#include "PhysicsEngine.hpp"
#include "LoginManager.hpp"

class GameUnit {
public:
	static const float WIDTH;
	static const float HEIGHT;
private:
	RenderWindow window;
	bool isGameActive;
	bool levelMenu;
	bool leaderboard;
	bool loginMenu, loggedIn;
	Font fontHeader, fontNormal;

	PlayerInfo players[2];
	LoginManager loginPlayer[2];
	//Leaderboard leaderboard;
	//Database manageSaves;
public:
	GameUnit() : isGameActive(false), levelMenu(false), leaderboard(false), loginMenu(false), loggedIn(false)
	{
		window.create(VideoMode({ 600,600 }), "SnowBros 25I-3014 25I-3039", Style::Close);
		window.setFramerateLimit(60);
		fontHeader.loadFromFile("SnowBrosAssets/Fonts/header-font.ttf");
		fontNormal.loadFromFile("SnowBrosAssets/Fonts/normal-font.ttf");
		loginPlayer[0].setFonts(fontHeader, fontNormal);
		loginPlayer[1].setFonts(fontHeader, fontNormal);
	}

	void launchGame();
	void drawLevel(int index);
	void drawMainMenu();
	void drawLeaderboard();
	void drawLoginMenu(int loginIndex);
	void drawTesting();
}; 
