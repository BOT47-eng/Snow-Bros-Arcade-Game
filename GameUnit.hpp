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
	RenderWindow window;
	bool isGameActive;
	bool levelMenu;
	bool loginMenu, loggedIn[2];
	Font fontHeader, fontNormal;

	PlayerInfo players[2];
	LoginManager loginPlayer[2];
	Leaderboard *leaderboardObj;
	LevelManager levelManager;
	//Database manageSaves;

	/////////////////////////////////
	// For MainMenu LeaderBoard Image
	Texture leaderBoardButtonTex;

public:
	GameUnit() : isGameActive(false), levelMenu(false), loginMenu(false)
	{
		window.create(VideoMode({ 600,600 }), "SnowBros 25I-3014 25I-3039", Style::Close);
		window.setFramerateLimit(60);
		fontHeader.loadFromFile("SnowBrosAssets/Fonts/header-font.ttf");
		fontNormal.loadFromFile("SnowBrosAssets/Fonts/normal-font.ttf");
		leaderBoardButtonTex.loadFromFile("Resources/SnowBrosAssets/Images/LeaderBoardButtonImage.jpg") ;
		loginPlayer[0].setFonts(fontHeader, fontNormal);
		loginPlayer[1].setFonts(fontHeader, fontNormal);

		loggedIn[0] = false;
		loggedIn[1] = false;

		leaderboardObj = new Leaderboard;
		leaderboardObj->drawLeaderboard = false;

		if (!levelManager.loadLevelConfig("Resources/SnowBrosAssets/Levels/LevelConfig.txt"))
			cout << "Could not Open Level Config File!" << endl;
	}

	void launchGame();
	void drawMainMenu();
	void drawLoginMenu(int loginIndex);
	void drawTesting();

	~GameUnit()
	{
		delete leaderboardObj;
		if (window.isOpen())
			window.close();
	}
}; 
