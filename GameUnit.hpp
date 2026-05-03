#pragma once
#include <SFML/Graphics.hpp>
#include <string>

#include "InputManager.hpp"
#include "Block.hpp"
#include "Player.hpp"
#include "PhysicsEngine.hpp"
#include "EnemyFactory.hpp"
#include "LoginManager.hpp"
#include "LeaderBoard.hpp"
#include "LevelManager.hpp"

class GameUnit {
public:
	static const float WIDTH;
	static const float HEIGHT;
private:
	sf::RenderWindow window;
	bool isGameActive;
	bool levelMenu;
	bool loginMenu, loggedIn[2];
	sf::Font fontHeader, fontNormal;

	PlayerInfo players[2];
	LoginManager loginPlayer[2];
	Leaderboard leaderboardObj;
	LevelManager levelManager;
	//Database manageSaves;

	/////////////////////////////////
	// For MainMenu LeaderBoard Image
	sf::Texture leaderBoardButtonTex;
	sf::Texture bg_tex;
	sf::Sprite bg_sprite;

public:
	GameUnit() : isGameActive(false), levelMenu(false), loginMenu(false), levelManager(&leaderboardObj)
	{
		window.create(sf::VideoMode({ 600,600 }), "SnowBros 25I-3014 25I-3039", sf::Style::Close);
		window.setFramerateLimit(60);
		fontHeader.loadFromFile("Resources/SnowBrosAssets/Fonts/header-font.ttf");
		fontNormal.loadFromFile("Resources/SnowBrosAssets/Fonts/normal-font.ttf");
		leaderBoardButtonTex.loadFromFile("Resources/SnowBrosAssets/Images/trophy.png") ;
		loginPlayer[0].setFonts(fontHeader, fontNormal);
		loginPlayer[1].setFonts(fontHeader, fontNormal);

		if (bg_tex.loadFromFile("Resources/Levels/Backgrounds/MainMenu.jpeg"))
			bg_sprite.setTexture(bg_tex);

		loggedIn[0] = false;
		loggedIn[1] = false;

		leaderboardObj.drawLeaderboard = false;

		if (!levelManager.loadLevelConfig("Resources/Levels/LevelConfig.txt"))
			std::cout << "Could not Open Level Config File!" << std::endl;
	}

	void launchGame();
	void drawMainMenu();
	void drawLoginMenu(int loginIndex);
	//void drawTesting();

	~GameUnit()
	{
		if (window.isOpen())
			window.close();
	}
}; 
