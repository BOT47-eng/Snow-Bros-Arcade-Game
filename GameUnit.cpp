#include "GameUnit.hpp"

using namespace std;
using namespace sf;

const float GameUnit::WIDTH = 600;
const float GameUnit::HEIGHT = 600;

void GameUnit::launchGame()
{

    drawMainMenu();

}

void GameUnit::drawLoginMenu(int loginIndex)
{
    Clock clock;
    float dt = 0;

    RectangleShape exitButton(Vector2f(80.f, 40.f));
    exitButton.setFillColor(Color::Yellow);
    exitButton.setPosition(Vector2f(505.f, 15.f));

    while (window.isOpen()) {
        Vector2i mousePos = Mouse::getPosition(window);
        dt = clock.restart().asSeconds();

        if (dt < 0.05)
            dt = 0.05;

        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) 
            {
                window.close();
            }

            if (event.type == Event::MouseButtonPressed)
            {
                if (exitButton.getGlobalBounds().contains(Vector2f(mousePos)))
                    return;
            }

            if (!loginPlayer[loginIndex].isLoggedIn()) {
                loginPlayer[loginIndex].handleInput(event, window);
            }

        }

        window.clear();

        string playerTextString = "";

        if (loginIndex == 0)
            playerTextString = "Player 1";
        else
            playerTextString = "Player 2";

        Text playerText(playerTextString, fontHeader, 20);
        playerText.setPosition(Vector2f(5, 5));

        window.draw(playerText);

        window.draw(exitButton);
        Text exitText("Exit", fontNormal, 50);
        exitText.setFillColor(Color::Black);
        exitText.setPosition(Vector2f(525.f, -10.f));
        window.draw(exitText);

        if (!loginPlayer[loginIndex].isLoggedIn())
        {
            loginPlayer[loginIndex].draw(window);
        }
        else 
        {
            if (loginIndex == 0)
            {
                loginPlayer[1].setOtherPlayer(loginPlayer[0].getCurrentUser());
                players[0] = loginPlayer[0].getCurrentUser();
                std::cout << "Login Player 1 Successful!" << std::endl;
            }
            else
            {
                loginPlayer[0].setOtherPlayer(loginPlayer[1].getCurrentUser());
                players[1] = loginPlayer[1].getCurrentUser();
                std::cout << "Login Player 2 Successful!" << std::endl;
            }

            return;
        }
        window.display();
    }
}

//void GameUnit::drawTesting()
//{
//    Player p1(0);
//    p1.setPosition(Vector2f(120.f, 480.f));
//
//    Player p2(1);
//    p2.setPosition(Vector2f(440.f, 480.f));
//
//    Enemy* enemy1 = new FlyingFoogaFoog;
//    enemy1->CreateEnemy(200.f, 200.f);
//
//    Enemy* enemy2 = new FlyingFoogaFoog;
//    enemy2->CreateEnemy(400.f, 250.f);
//
//    Enemy* enemy3 = new Botom;
//    enemy3->CreateEnemy(300.f, 100.f);
//
//    Enemy* enemies[3] = { enemy1, enemy2, enemy3 };
//
//    const int BLOCK_COUNT = 11;
//    Block blocks[BLOCK_COUNT] = {
//        Block(-200.f, 560.f, 1000.f, 40.f),
//        Block(0.f, 460.f, 160.f, 16.f),
//        Block(500.f, 460.f, 160.f, 16.f),
//        Block(100.f, 360.f, 96.f, 16.f),
//        Block(300.f, 360.f, 80.f, 16.f),
//        Block(504.f, 360.f, 96.f, 16.f),
//        Block(64.f, 260.f, 100.f, 16.f),
//        Block(256.f, 260.f, 288.f, 16.f),
//        Block(608.f, 260.f, 128.f, 16.f),
//        Block(160.f, 160.f, 160.f, 16.f),
//        Block(480.f, 160.f, 160.f, 16.f),
//    };
//
//    PhysicsEngine physics;
//    for (int i = 0; i < BLOCK_COUNT; i++)
//        physics.addPlatform(&blocks[i]);
//
//    InputManager input;
//
//    bool fontOk = fontHeader.loadFromFile("Resources/SnowBrosAssets/Fonts/header-font.ttf");
//
//    Text hudText;
//    if (fontOk)
//    {
//        hudText.setFont(fontHeader);
//        hudText.setCharacterSize(16);
//        hudText.setFillColor(Color::White);
//    }
//
//    bool debugOn = false;
//
//    RectangleShape bg(Vector2f(WIDTH, HEIGHT));
//    bg.setFillColor(Color::Black);
//
//    Clock clock;
//
//    while (window.isOpen())
//    {
//        float dt = clock.restart().asSeconds();
//
//        if (dt > 0.05f)
//            dt = 0.05f;
//
//        input.resetInput();
//
//        Event event;
//        while (window.pollEvent(event))
//        {
//            if (event.type == Event::Closed)
//                window.close();
//            input.handleEvent(event);
//        }
//
//        if (input.debug())
//            debugOn = !debugOn;
//        if (input.gamePause())
//            window.close();
//
//        p1.handleInput(input, dt);
//        p2.handleInput(input, dt);
//
//        physics.update(p1, p2, enemies, 3, dt, window, fontNormal);
//
//        p1.update(dt);
//        p2.update(dt);
//
//        window.clear();
//        window.draw(bg);
//
//        for (int i = 0; i < BLOCK_COUNT; i++)
//            blocks[i].draw(window, debugOn);
//
//        p1.draw(window, debugOn);
//        p2.draw(window, debugOn);
//
//        for (int i = 0; i < 3; i++)
//        {
//            if (enemies[i])
//                enemies[i]->draw(window, debugOn);
//        }
//
//        if (fontOk)
//        {
//            hudText.setString(players[0].username + "  Lives:" + to_string(p1.getLives()) +
//                "  Score:" + to_string(p1.getScore()));
//            hudText.setPosition(8.f, 4.f);
//            window.draw(hudText);
//
//            hudText.setString(players[1].username + "  Lives:" + to_string(p2.getLives()) +
//                "  Score:" + to_string(p2.getScore()));
//            hudText.setPosition(8.f, 24.f);
//            window.draw(hudText);
//
//            hudText.setString("F1/H: hitboxes    ESC/P: quit");
//            hudText.setPosition(8.f, HEIGHT - 24.f);
//            window.draw(hudText);
//        }
//
//        window.display();
//    }
//
//    for (int i = 0; i < 3; i++)
//    {
//        if (enemies[i])
//        {
//            delete enemies[i];
//            enemies[i] = nullptr;
//        }
//    }
//}

void GameUnit::drawMainMenu()
{

    Clock clock;
    float dt = 0;

    Text gameTitle("SnowBros", fontHeader, 40);
    gameTitle.setPosition(Vector2f(10, 10));

    Text gameCredits("25I-3014 and 25I-3039", fontHeader, 16);
    gameCredits.setPosition(Vector2f(10, 65));

    /*RectangleShape horizontalLine, verticalLine;

    verticalLine.setSize(Vector2f(1, 600));
    verticalLine.setFillColor(Color::White);
    verticalLine.setPosition(Vector2f(300, 0));

    horizontalLine.setSize(Vector2f(1, 600));
    horizontalLine.setFillColor(Color::White);
    horizontalLine.setPosition(Vector2f(0, 300));
    horizontalLine.setRotation(-90);*/

    //New Game, Continue Game, Guest Mode, Quit Game
    const int noOfOptions = 4;
    RectangleShape playOptions[noOfOptions];
    RectangleShape loginOptions[2];

    for (int i = 0; i < noOfOptions; i++)
    {
        playOptions[i].setSize(Vector2f(200, 40));
        playOptions[i].setFillColor(Color::Yellow);

        if (i < 2)
        {
            loginOptions[i].setSize(Vector2f(280, 40));
            loginOptions[i].setFillColor(Color::Yellow);
        }

    }

    playOptions[0].setPosition(Vector2f(10, 150));
    playOptions[1].setPosition(Vector2f(10, 200));
    playOptions[2].setPosition(Vector2f(10, 250));
    playOptions[3].setPosition(Vector2f(10, 350));

    loginOptions[0].setPosition(Vector2f(10, 550));
    loginOptions[1].setPosition(Vector2f(310, 550));

    RectangleShape leaderboardContainer(Vector2f(40, 40));
    leaderboardContainer.setTexture(&leaderBoardButtonTex) ;
    leaderboardContainer.setPosition(Vector2f(550, 10));

    string loginLabels[2] = { "", "" };
    string loginStrings[2] = { "Login Player 1", "Login Player 2" };
    string playOptionsStrings[noOfOptions] = { "New Game", "Continue Game", "Guest Mode", "Quit Game" };

    Text playOptionsTexts[noOfOptions] = { Text(playOptionsStrings[0], fontNormal, 60), Text(playOptionsStrings[1], fontNormal, 60), Text(playOptionsStrings[2], fontNormal, 60), Text(playOptionsStrings[3], fontNormal, 60) };

    for (int i = 0; i < noOfOptions; i++)
    {
        playOptionsTexts[i].setFillColor(Color::Black);
    }

    playOptionsTexts[0].setPosition(Vector2f(15, 120));
    playOptionsTexts[1].setPosition(Vector2f(15, 170));
    playOptionsTexts[2].setPosition(Vector2f(15, 220));
    playOptionsTexts[3].setPosition(Vector2f(15, 320));

    Text loginLabelsText[2] = { Text("Guest", fontNormal, 40), Text("Guest", fontNormal, 40)};
    loginLabelsText[0].setPosition(Vector2f(10, 500));
    loginLabelsText[1].setPosition(Vector2f(310, 500));

    //Change to black in future
    loginLabelsText[0].setFillColor(Color::White);
    loginLabelsText[1].setFillColor(Color::White);

    Text loginOptionsTexts[2] = { Text(loginStrings[0], fontNormal, 60), Text(loginStrings[1], fontNormal, 60) };
    loginOptionsTexts[0].setPosition(Vector2f(15, 520));
    loginOptionsTexts[1].setPosition(Vector2f(315, 520));

    loginOptionsTexts[0].setFillColor(Color::Black);
    loginOptionsTexts[1].setFillColor(Color::Black);

    Vector2i mousePos;

    while (window.isOpen()) {
        mousePos = Mouse::getPosition(window);
        dt = clock.restart().asSeconds();

        if (dt < 0.05)
            dt = 0.05;

        Event event; 
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
            {
                window.close();
            }

            if (event.type == Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == Mouse::Button::Left)
                {
                    //New game
                    if (playOptions[0].getGlobalBounds().contains(Vector2f(mousePos)))
                    {
                        if (loginPlayer[0].isLoggedIn() || loginPlayer[1].isLoggedIn())
                        {
                            levelManager.startGame(0, &window, &fontHeader, &fontNormal, players, loginPlayer[0].isLoggedIn(), loginPlayer[1].isLoggedIn());
                        }
                    }
                    //Continue game
                    else if (playOptions[1].getGlobalBounds().contains(Vector2f(mousePos)))
                    {
                        if (loginPlayer[0].isLoggedIn() || loginPlayer[1].isLoggedIn())
                        {
                            levelManager.startGame(1, &window, &fontHeader, &fontNormal, players, loginPlayer[0].isLoggedIn(), loginPlayer[1].isLoggedIn());
                        }
                    }
                    //Guest mode
                    else if (playOptions[2].getGlobalBounds().contains(Vector2f(mousePos)))
                    {
                        levelManager.startGame(2, &window, &fontHeader, &fontNormal, players, loginPlayer[0].isLoggedIn(), loginPlayer[1].isLoggedIn());
                    }
                    //Quit game
                    else if (playOptions[3].getGlobalBounds().contains(Vector2f(mousePos)))
                    {
                        window.close();
                    }
                    //Login player 1
                    else if (loginOptions[0].getGlobalBounds().contains(Vector2f(mousePos)))
                    {
                        if (!loginPlayer[0].isLoggedIn())
                            drawLoginMenu(0);
                        else
                            loginPlayer[0].logout();
                    }
                    //Login player 2
                    else if (loginOptions[1].getGlobalBounds().contains(Vector2f(mousePos)))
                    {
                        if (!loginPlayer[1].isLoggedIn())
                            drawLoginMenu(1);
                        else
                            loginPlayer[1].logout();
                    }
                    //Leaderboard
                    else if (leaderboardContainer.getGlobalBounds().contains(Vector2f(mousePos)))
                    {
                        leaderboardObj.loadFromFile();
                        leaderboardObj.drawLeaderboard = true;
                    }
                }
            }

        }

        for (int i = 0; i < noOfOptions; i++)
        {
            if (playOptions[i].getGlobalBounds().contains(Vector2f(mousePos)))
            {
                playOptionsTexts[i].setFillColor(Color::Red);
            }
            else
            {
                playOptionsTexts[i].setFillColor(Color::Black);
            }

            if (i < 2)
            {
                if (loginOptions[i].getGlobalBounds().contains(Vector2f(mousePos)))
                {
                    loginOptionsTexts[i].setFillColor(Color::Red);
                }
                else
                {
                    loginOptionsTexts[i].setFillColor(Color::Black);
                }
            }

        }

        if (!loginPlayer[0].isLoggedIn())
        {
            loginOptionsTexts[0].setString("Login Player 1");
            loginLabelsText[0].setString("Guest");
        }
        else
        {
            loginOptionsTexts[0].setString("Logout Player 1");
            loginLabelsText[0].setString(loginPlayer[0].getCurrentUser().username);
        }

        if (!loginPlayer[1].isLoggedIn())
        {
            loginOptionsTexts[1].setString("Login Player 2");
            loginLabelsText[1].setString("Guest");
        }
        else
        {
            loginOptionsTexts[1].setString("Logout Player 2");
            loginLabelsText[1].setString(loginPlayer[1].getCurrentUser().username);
        }

        window.clear();

        for (int i = 0; i < noOfOptions; i++)
        {
            window.draw(playOptions[i]);

            if (i < 2)
            {
                window.draw(loginLabelsText[i]);
                window.draw(loginOptions[i]);
                window.draw(loginOptionsTexts[i]);
            }

            window.draw(playOptionsTexts[i]);
        }

        window.draw(gameTitle);
        window.draw(gameCredits);
        window.draw(leaderboardContainer);

        /*window.draw(verticalLine);
        window.draw(horizontalLine);*/

        
        while(leaderboardObj.drawLeaderboard == true)
        {
            leaderboardObj.draw(window);
        }
        window.display();
    }

}