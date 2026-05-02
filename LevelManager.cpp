#include "LevelManager.hpp"

LevelManager::LevelManager() : levels(nullptr), levelCount(0), levelUnlocked(nullptr), levelCompleted(nullptr), window(nullptr), fontHeader(nullptr), fontNormal(nullptr), players(nullptr), player1Active(false), player2Active(false), isSinglePlayer(false), p1(0), p2(1), shop(nullptr)
{}

LevelManager::~LevelManager()
{
	if (levels) 
	{
		for (int i = 0; i < levelCount; i++) 
		{
			if (levels[i].enemies)
				delete[] levels[i].enemies;
			if (levels[i].blocks)
				delete[] levels[i].blocks;
		}
		delete[] levels;
	}
	if (levelUnlocked)
		delete[] levelUnlocked;
	if (levelCompleted)
		delete[] levelCompleted;
}

bool LevelManager::loadLevelConfig(const string& filepath)
{
	ifstream file;

	file.open(filepath);

	if (!file.is_open())
		return false;

	file >> levelCount;
	if (levelCount <= 0)
		return false;

	levels = new LevelData[levelCount];
	levelUnlocked = new bool[levelCount];
	levelCompleted = new bool[levelCount];

	levelUnlocked[0] = true;
	if (!player1Active && !player2Active)
	{
		for (int i = 1; i < levelCount; i++)
			levelUnlocked[i] = false;
	}
	else
	{
		for (int i = 1; i < levelCount; i++)
			levelUnlocked[i] = false;
	}

	for (int i = 0; i < levelCount; i++)
		levelCompleted[i] = false;

	for (int i = 0; i < levelCount; i++) 
	{
		file >> levels[i].levelNumber >> levels[i].isBossLevel >> levels[i].enemyCount;

		levels[i].enemies = new EnemyData[levels[i].enemyCount];
		for (int j = 0; j < levels[i].enemyCount; j++) 
		{
			file >> levels[i].enemies[j].type >> levels[i].enemies[j].x >> levels[i].enemies[j].y;
		}

		if (!(file >> levels[i].blockCount)) {
			cout << "Error: Could not read blockCount for level " << levels[i].levelNumber << endl;
			return false;
		}

		if (levels[i].blockCount > 80) 
		{
			cout << "Level " << levels[i].levelNumber << " exceeds 80 block limit" << endl;
			return false;
		}

		levels[i].blocks = new BlockData[levels[i].blockCount];
		for (int j = 0; j < levels[i].blockCount; j++) 
		{
			file >> levels[i].blocks[j].x >> levels[i].blocks[j].y >> levels[i].blocks[j].width >> levels[i].blocks[j].height;
		}
	}

	file.close();
	return true;
}

Enemy* LevelManager::createEnemy(const string& type, float x, float y)
{
	Enemy* enemy = nullptr;
	if (type == "FlyingFoogaFoog") 
	{
		enemy = new FlyingFoogaFoog;
		enemy->CreateEnemy(x, y);
	}
	else if (type == "Botom") 
	{
		enemy = new Botom;
		enemy->CreateEnemy(x, y);
	}
	return enemy;
}

int LevelManager::getLevelCount()
{
	return levelCount;
}

bool LevelManager::isLevelUnlocked(int levelIndex)
{
	if (levelIndex >= 0 && levelIndex < levelCount)
		return levelUnlocked[levelIndex];
	return false;
}

bool LevelManager::isLevelCompleted(int levelIndex)
{
	if (levelIndex >= 0 && levelIndex < levelCount)
		return levelCompleted[levelIndex];
	return false;
}

void LevelManager::setLevelCompleted(int levelIndex)
{
	if (levelIndex >= 0 && levelIndex < levelCount) 
	{
		levelCompleted[levelIndex] = true;
		if (levelIndex + 1 < levelCount)
			levelUnlocked[levelIndex + 1] = true;
	}
}

bool LevelManager::runLevel(int levelIndex, Player& p1, Player& p2)
{
	if (levelIndex < 0 || levelIndex >= levelCount)
		return false;

	const int RESUME = 0;
	const int SHOP_1 = 1;
	const int SHOP_2 = 2;
	const int RETURN_MENU = 3;
	const int QUIT_GAME = 4;
	bool enemiesAlive = false;

	LevelData& level = levels[levelIndex];
	PhysicsEngine physics;

	Block* blockArray = new Block[level.blockCount];
	for (int i = 0; i < level.blockCount; i++) 
	{
		blockArray[i] = Block(level.blocks[i].x, level.blocks[i].y, level.blocks[i].width, level.blocks[i].height);
		physics.addPlatform(&blockArray[i]);
	}

	Enemy** enemies = new Enemy*[level.enemyCount];
	for (int i = 0; i < level.enemyCount; i++) 
	{
		enemies[i] = createEnemy(level.enemies[i].type, level.enemies[i].x, level.enemies[i].y);
	}

	InputManager input;
	Clock clock;
	RectangleShape bg(Vector2f(600, 600));
	bg.setFillColor(Color::Black);

	Text hudText;
	hudText.setFont(*fontHeader);
	hudText.setCharacterSize(12);
	hudText.setFillColor(Color::White);

	bool debugOn = false;
	bool paused = false;

	while (window->isOpen()) 
	{
		float dt = clock.restart().asSeconds();
		if (dt > 0.05f)
			dt = 0.05f;

		enemiesAlive = false;

		input.resetInput();

		Event event;
		while (window->pollEvent(event)) {
			if (event.type == Event::Closed) {
				window->close();
				for (int i = 0; i < level.blockCount; i++) 
				{
					blockArray[i].~Block();
				}
				for (int i = 0; i < level.enemyCount; i++) 
				{
					if (enemies[i]) {
						delete enemies[i];
						enemies[i] = nullptr;
					}
				}
				delete[] blockArray;
				delete[] enemies;
				return false;
			}

			input.handleEvent(event);

			if (event.type == Event::KeyPressed) 
			{
				if (event.key.code == Keyboard::Escape || event.key.code == Keyboard::P) {
					paused = !paused;
				}
			}
		}

		if (paused) 
		{
			int menuChoice = drawPauseMenu(p1, p2, isSinglePlayer);
			if (menuChoice == RESUME) 
			{
				paused = false;
			}
			else if (menuChoice == SHOP_1) 
			{
				drawShop(p1, isSinglePlayer);
				paused = true;
			}
			else if (menuChoice == SHOP_2)
			{
				drawShop(p2, isSinglePlayer);
				paused = true;
			}
			else if (menuChoice == RETURN_MENU) 
			{
				for (int i = 0; i < level.blockCount; i++) 
				{
					blockArray[i].~Block();
				}
				for (int i = 0; i < level.enemyCount; i++) 
				{
					if (enemies[i]) {
						delete enemies[i];
						enemies[i] = nullptr;
					}
				}
				delete[] blockArray;
				delete[] enemies;
				return false;
			}
			else if (menuChoice == QUIT_GAME) {
				window->close();
				for (int i = 0; i < level.blockCount; i++) 
				{
					blockArray[i].~Block();
				}
				for (int i = 0; i < level.enemyCount; i++) 
				{
					if (enemies[i]) 
					{
						delete enemies[i];
						enemies[i] = nullptr;
					}
				}
				delete[] blockArray;
				delete[] enemies;
				return false;
			}
			continue;
		}

		if (input.debug())
			debugOn = !debugOn;

		if (isSinglePlayer) 
		{
			if (player1Active)
				p1.handleInput(input, dt);
			else
				p2.handleInput(input, dt);
		}
		else 
		{
			p1.handleInput(input, dt);
			p2.handleInput(input, dt);
		}

		if (isSinglePlayer) 
		{
			if (player1Active)
				physics.update(p1, enemies, level.enemyCount, dt);
			else
				physics.update(p2, enemies, level.enemyCount, dt);
		}
		else 
		{
			physics.update(p1, p2, enemies, level.enemyCount, dt);
		}

		if (isSinglePlayer)
		{
			if (player1Active)
				p1.update(dt);
			else
				p2.update(dt);
		}
		else
		{
			p1.update(dt);
			p2.update(dt);
		}

		bool p1Alive = false;
		bool p2Alive = false;
		
		if (isSinglePlayer)
		{
			if (player1Active)
			{
				p1Alive = p1.getLives() > 0;
				p2Alive = false;
			}
			else
			{
				p2Alive = p2.getLives() > 0;
				p1Alive = false;
			}
		}
		else
		{
			p1Alive = p1.getLives() > 0;
			p2Alive = p2.getLives() > 0;
		}

		for (int i = 0; i < level.enemyCount; i++)
		{
			if (enemies[i])
				enemiesAlive = true;
		}

		if ((!p1Alive && !p2Alive) || !enemiesAlive) 
		{
			drawGameOver(p1.getScore(), p2.getScore(), p1Alive, p2Alive);
			for (int i = 0; i < level.blockCount; i++) 
			{
				blockArray[i].~Block();
			}
			for (int i = 0; i < level.enemyCount; i++) 
			{
				if (enemies[i]) 
				{
					delete enemies[i];
					enemies[i] = nullptr;
				}
			}

			if (p1Alive || p2Alive)
				setLevelCompleted(levelIndex);

			delete[] blockArray;
			delete[] enemies;
			return false;
		}

		window->clear();
		window->draw(bg);

		for (int i = 0; i < level.blockCount; i++)
			blockArray[i].draw(*window, debugOn);

		if (isSinglePlayer)
		{
			if (player1Active)
				p1.draw(*window, debugOn);
			else
				p2.draw(*window, debugOn);
		}
		else
		{
			p1.draw(*window, debugOn);
			p2.draw(*window, debugOn);
		}	

		for (int i = 0; i < level.enemyCount; i++) 
		{
			if (enemies[i])
				enemies[i]->draw(*window, debugOn);
		}

		if (isSinglePlayer) 
		{
			if (player1Active) 
			{
				hudText.setString(players[0].username + "  Lives:" + to_string(p1.getLives()) +
					"  Score:" + to_string(p1.getScore()));
			}
			else 
			{
				hudText.setString(players[1].username + "  Lives:" + to_string(p2.getLives()) +
					"  Score:" + to_string(p2.getScore()));
			}
		}
		else 
		{
			hudText.setString(players[0].username + "  Lives:" + to_string(p1.getLives()) +
				"  Score:" + to_string(p1.getScore()));
		}
		hudText.setPosition(8.f, 4.f);
		window->draw(hudText);

		if (!isSinglePlayer) 
		{
			hudText.setString(players[1].username + "  Lives:" + to_string(p2.getLives()) +
				"  Score:" + to_string(p2.getScore()));
			hudText.setPosition(8.f, 24.f);
			window->draw(hudText);
		}

		if (level.isBossLevel) 
		{
			hudText.setString("BOSS LEVEL");
			hudText.setPosition(500.f, 4.f);
			window->draw(hudText);
		}

		hudText.setString("F1/H: hitboxes    ESC/P: pause");
		hudText.setPosition(8.f, 576.f);
		window->draw(hudText);

		window->display();
	}

	for (int i = 0; i < level.blockCount; i++) {
		blockArray[i].~Block();
	}
	for (int i = 0; i < level.enemyCount; i++) {
		if (enemies[i]) {
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}
	delete[] blockArray;
	delete[] enemies;
	return enemiesAlive;
}

void LevelManager::drawLevelSelect(int gameMode)
{
	Clock clock;
	const int LEVELS_PER_ROW = 5;
	const float LEVEL_SIZE = 100.f;
	const float SPACING = 15.f;

	while (window->isOpen()) {
		float dt = clock.restart().asSeconds();

		if (dt < 0.05f)
			dt = 0.05f;

		Vector2i mousePos = Mouse::getPosition(*window);

		Event event;
		while (window->pollEvent(event)) {
			if (event.type == Event::Closed) {
				window->close();
				return;
			}

			if (event.type == Event::MouseButtonPressed) {
				if (event.mouseButton.button == Mouse::Button::Left) {
					for (int i = 0; i < levelCount; i++) {
						int row = i / LEVELS_PER_ROW;
						int col = i % LEVELS_PER_ROW;
						float x = 20.f + col * (LEVEL_SIZE + SPACING);
						float y = 100.f + row * (LEVEL_SIZE + SPACING);

						RectangleShape levelBox(Vector2f(LEVEL_SIZE, LEVEL_SIZE));
						levelBox.setPosition(Vector2f(x, y));

						if (levelBox.getGlobalBounds().contains(Vector2f(mousePos))) {
							if (levelUnlocked[i]) 
							{
								if (isSinglePlayer) {
									if (player1Active) {
										p1.setPosition(Vector2f(300.f, 480.f));
									}
									else {
										p2.setPosition(Vector2f(300.f, 480.f));
									}
								}
								else {
									p1.setPosition(Vector2f(120.f, 480.f));
									p2.setPosition(Vector2f(440.f, 480.f));
								}

								runLevel(i, p1, p2);
							}
						}
					}

					RectangleShape backButton(Vector2f(80.f, 40.f));
					backButton.setPosition(Vector2f(10.f, 10.f));
					if (backButton.getGlobalBounds().contains(Vector2f(mousePos))) {
						return;
					}
				}
			}
		}

		window->clear();

		RectangleShape backButton(Vector2f(80.f, 40.f));
		backButton.setFillColor(Color::Yellow);
		backButton.setPosition(Vector2f(10.f, 10.f));
		window->draw(backButton);

		Text backText("Back", *fontNormal, 50);
		backText.setFillColor(Color::Black);
		backText.setPosition(Vector2f(25.f, -15.f));
		window->draw(backText);

		for (int i = 0; i < levelCount; i++) {
			int row = i / LEVELS_PER_ROW;
			int col = i % LEVELS_PER_ROW;
			float x = 20.f + col * (LEVEL_SIZE + SPACING);
			float y = 100.f + row * (LEVEL_SIZE + SPACING);

			RectangleShape levelBox(Vector2f(LEVEL_SIZE, LEVEL_SIZE));
			levelBox.setPosition(Vector2f(x, y));

			if (levelUnlocked[i]) 
			{
				if (levelCompleted[i])
					levelBox.setFillColor(Color::Green);
				else
					levelBox.setFillColor(Color::Yellow);
			}
			else 
			{
				levelBox.setFillColor(Color::Blue);
			}

			window->draw(levelBox);

			Text levelNumber(to_string(i + 1), *fontNormal, 55);
			levelNumber.setFillColor(Color::Black);
			levelNumber.setPosition(Vector2f(x + 10.f, y - 25.f));
			window->draw(levelNumber);

			if (levels[i].isBossLevel) 
			{
				RectangleShape bossIndicator(Vector2f(10.f, 10.f));
				bossIndicator.setFillColor(Color::Red);
				bossIndicator.setPosition(Vector2f(x + 85.f, y + 5.f));
				window->draw(bossIndicator);
			}

			if (!levelUnlocked[i]) {
				Text lockText("L", *fontNormal, 60);
				lockText.setFillColor(Color::Red);
				lockText.setPosition(Vector2f(x + 10.f, y + 25.f));
				window->draw(lockText);
			}
		}

		window->display();
	}
}

int LevelManager::drawPauseMenu(Player& p1, Player& p2, bool singlePlayer)
{
	Clock clock;
	const float BUTTON_WIDTH = 150.f;
	const float BUTTON_HEIGHT = 50.f;
	const float START_X = 225.f;
	const float START_Y = 150.f;
	const float SPACING = 70.f;
	const int RESUME = 0;
	const int SHOP = 1;
	const int SHOP_P2 = 2;
	const int RETURN_MENU = 3;
	const int QUIT_GAME = 4;

	int buttonCount = 5;
	
	if (singlePlayer) 
		buttonCount = 4;

	RectangleShape buttons[5];
	for (int i = 0; i < buttonCount; i++) 
	{
		buttons[i].setSize(Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT));
		buttons[i].setFillColor(Color::Yellow);
		buttons[i].setPosition(Vector2f(START_X, START_Y + i * SPACING));
	}

	string buttonLabels[5];
	if (singlePlayer) 
	{
		buttonLabels[0] = "Resume";
		buttonLabels[1] = "Shop";
		buttonLabels[2] = "Main Menu";
		buttonLabels[3] = "Quit Game";
	}
	else 
	{
		buttonLabels[0] = "Resume";
		buttonLabels[1] = "Shop P1";
		buttonLabels[2] = "Shop P2";
		buttonLabels[3] = "Main Menu";
		buttonLabels[4] = "Quit Game";
	}

	Text buttonTexts[5];
	for (int i = 0; i < buttonCount; i++) 
	{
		buttonTexts[i].setString(buttonLabels[i]);
		buttonTexts[i].setFont(*fontNormal);
		buttonTexts[i].setCharacterSize(40);
		buttonTexts[i].setFillColor(Color::Black);
		buttonTexts[i].setPosition(Vector2f(START_X + 20.f, START_Y + i * SPACING - 10.f));
	}

	while (window->isOpen()) {
		float dt = clock.restart().asSeconds();
		if (dt < 0.05f)
			dt = 0.05f;

		Vector2i mousePos = Mouse::getPosition(*window);

		Event event;
		while (window->pollEvent(event)) 
		{
			if (event.type == Event::Closed) 
			{
				window->close();
				return QUIT_GAME;
			}

			if (event.type == Event::MouseButtonPressed) 
			{
				if (event.mouseButton.button == Mouse::Button::Left) 
				{
					for (int i = 0; i < buttonCount; i++) 
					{
						if (buttons[i].getGlobalBounds().contains(Vector2f(mousePos))) 
						{
							if (singlePlayer) 
							{
								if (i == RESUME)
									return RESUME;
								else if (i == SHOP) 
								{
									if (player1Active)
										drawShop(p1, true);
									else
										drawShop(p2, true);
									return RESUME;
								}
								else if (i == 2)
									return RETURN_MENU;
								else if (i == 3)
									return QUIT_GAME;
							}
							else 
							{
								if (i == RESUME)
									return RESUME;
								else if (i == SHOP)
									drawShop(p1, false);
								else if (i == SHOP_P2)
									drawShop(p2, false);
								else if (i == 3)
									return RETURN_MENU;
								else if (i == 4)
									return QUIT_GAME;
								return RESUME;
							}
						}
					}
				}
			}

			if (event.type == Event::KeyPressed) 
			{
				if (event.key.code == Keyboard::Escape || event.key.code == Keyboard::P) 
				{
					return RESUME;
				}
			}
		}

		for (int i = 0; i < buttonCount; i++) 
		{
			if (buttons[i].getGlobalBounds().contains(Vector2f(mousePos))) 
			{
				buttonTexts[i].setFillColor(Color::Red);
			}
			else {
				buttonTexts[i].setFillColor(Color::Black);
			}
		}

		window->clear();

		RectangleShape overlay(Vector2f(600.f, 600.f));
		overlay.setFillColor(Color(0, 0, 0, 150));
		window->draw(overlay);

		Text pauseTitle("PAUSED", *fontHeader, 40);
		pauseTitle.setFillColor(Color::White);
		pauseTitle.setPosition(Vector2f(200.f, 50.f));
		window->draw(pauseTitle);

		for (int i = 0; i < buttonCount; i++) 
		{
			window->draw(buttons[i]);
			window->draw(buttonTexts[i]);
		}

		window->display();
	}

	return QUIT_GAME;
}

void LevelManager::drawShop(Player& player, bool singlePlayer)
{
	Clock clock;

	if (shop == nullptr)
		shop = new Shop();

	RectangleShape exitButton(Vector2f(80.f, 40.f));
	exitButton.setFillColor(Color::Yellow);
	exitButton.setPosition(Vector2f(10.f, 15.f));

	while (window->isOpen()) {
		float dt = clock.restart().asSeconds();
		if (dt < 0.05f)
			dt = 0.05f;

		Vector2i mousePos = Mouse::getPosition(*window);

		Event event;
		while (window->pollEvent(event)) 
		{
			if (event.type == Event::Closed) 
			{
				window->close();
				return;
			}

			if (event.type == Event::MouseButtonPressed) 
			{
				if (event.mouseButton.button == Mouse::Button::Left) 
				{
					if (exitButton.getGlobalBounds().contains(Vector2f(mousePos))) 
					{
						return;
					}
				}
			}

			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Escape) 
				{
					return;
				}
			}
		}

		window->clear();

		shop->draw(*window, player);

		window->draw(exitButton);

		Text exitText("Exit", *fontNormal, 50);
		exitText.setFillColor(Color::Black);
		exitText.setPosition(Vector2f(25.f, -12.f));
		window->draw(exitText);

		window->display();
	}
}

void LevelManager::drawGameOver(int p1Score, int p2Score, bool p1Alive, bool p2Alive)
{
	Clock clock;

	while (window->isOpen()) {
		float dt = clock.restart().asSeconds();
		if (dt < 0.05f)
			dt = 0.05f;

		Vector2i mousePos = Mouse::getPosition(*window);

		Event event;
		while (window->pollEvent(event)) {
			if (event.type == Event::Closed) {
				window->close();
				return;
			}

			if (event.type == Event::MouseButtonPressed) {
				if (event.mouseButton.button == Mouse::Button::Left) {
					RectangleShape retryButton(Vector2f(100.f, 40.f));
					retryButton.setPosition(Vector2f(150.f, 300.f));

					RectangleShape quitButton(Vector2f(100.f, 40.f));
					quitButton.setPosition(Vector2f(350.f, 300.f));

					if (retryButton.getGlobalBounds().contains(Vector2f(mousePos))) {
						return;
					}
					if (quitButton.getGlobalBounds().contains(Vector2f(mousePos))) {
						return;
					}
				}
			}
		}

		window->clear();

		string gameOverStr = "";

		if (p1Alive || p2Alive)
			gameOverStr = "Completed";
		else
			gameOverStr = "Game Over";

		Text gameOverText(gameOverStr, *fontHeader, 40);
		gameOverText.setFillColor(Color::Red);
		gameOverText.setPosition(Vector2f(150.f, 100.f));
		window->draw(gameOverText);

		Text p1ScoreText("Player 1 Score: " + to_string(p1Score), *fontNormal, 60);
		p1ScoreText.setFillColor(Color::White);
		p1ScoreText.setPosition(Vector2f(100.f, 160.f));
		window->draw(p1ScoreText);

		Text p2ScoreText("Player 2 Score: " + to_string(p2Score), *fontNormal, 60);
		p2ScoreText.setFillColor(Color::White);
		p2ScoreText.setPosition(Vector2f(100.f, 200.f));
		window->draw(p2ScoreText);

		RectangleShape retryButton(Vector2f(100.f, 40.f));
		retryButton.setFillColor(Color::Yellow);
		retryButton.setPosition(Vector2f(150.f, 300.f));
		window->draw(retryButton);

		string retryStr = "";

		if (p1Alive || p2Alive)
			retryStr = "Next";
		else
			retryStr = "Retry";

		Text retryText(retryStr, *fontNormal, 50);
		retryText.setFillColor(Color::Black);
		retryText.setPosition(Vector2f(170.f, 280.f));
		window->draw(retryText);

		RectangleShape quitButton(Vector2f(100.f, 40.f));
		quitButton.setFillColor(Color::Yellow);
		quitButton.setPosition(Vector2f(350.f, 300.f));
		window->draw(quitButton);

		Text quitText("Quit", *fontNormal, 50);
		quitText.setFillColor(Color::Black);
		quitText.setPosition(Vector2f(375.f, 280.f));
		window->draw(quitText);

		window->display();
	}
}

void LevelManager::startGame(int gameMode, RenderWindow* window, Font* fHeader, Font* fNormal, PlayerInfo* playerInfo, bool p1Login, bool p2Login)
{
	this->window = window;
	fontHeader = fHeader;
	fontNormal = fNormal;
	players = playerInfo;
	player1Active = p1Login;
	player2Active = p2Login;

	if ((p1Login && !p2Login) || (!p1Login && p2Login))
		isSinglePlayer = true;
	else
		isSinglePlayer = false;

	drawLevelSelect(gameMode);
}