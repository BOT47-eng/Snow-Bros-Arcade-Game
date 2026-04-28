#include "GameUnit.hpp"

using namespace std;
using namespace sf;

const float GameUnit::WIDTH = 600;
const float GameUnit::HEIGHT = 600;

void GameUnit::launchGame()
{
    //Latter on, button will be there for both players
    drawLoginMenu(0);
    loggedIn = loginPlayer[0].isLoggedIn();

    if (loggedIn)
        loginPlayer[1].setOtherPlayer(loginPlayer[0].getCurrentUser());

    drawLoginMenu(1);
    loggedIn = loginPlayer[1].isLoggedIn();

    players[0] = loginPlayer[0].getCurrentUser();
    players[1] = loginPlayer[1].getCurrentUser();

    if (loggedIn)
        drawTesting();

}

void GameUnit::drawLoginMenu(int loginIndex)
{
    Clock clock;
    float dt = 0;

    while (window.isOpen()) {

        dt = clock.restart().asSeconds();

        if (dt < 0.05)
            dt = 0.05;

        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) 
            {
                window.close();
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

        if (!loginPlayer[loginIndex].isLoggedIn())
        {
            loginPlayer[loginIndex].draw(window);
        }
        else 
        {
            if (loginIndex == 0)
            {
                cout << "Login Player 1 Successful!" << endl;
            }
            else
            {
                cout << "Login Player 2 Successful!" << endl;
            }

            return;
        }
        window.display();
    }
}

void GameUnit::drawTesting()
{
    Player p1(0);
    p1.setPosition(Vector2f(120.f, 480.f));

    Player p2(1);
    p2.setPosition(Vector2f(440.f, 480.f));

    const int BLOCK_COUNT = 11;
    Block blocks[BLOCK_COUNT] = {
        Block(0.f, 560.f, 800.f, 40.f),   // ground floor
        Block(0.f, 460.f, 160.f, 16.f),   // low-left
        Block(500.f, 460.f, 160.f, 16.f),   // low-right
        Block(100.f, 360.f,  96.f, 16.f),   // mid-left
        Block(300.f, 360.f,  80.f, 16.f),   // mid-centre
        Block(504.f, 360.f,  96.f, 16.f),   // mid-right
        Block(64.f, 260.f, 100.f, 16.f),   // upper-left
        Block(256.f, 260.f, 288.f, 16.f),   // upper-centre
        Block(608.f, 260.f, 128.f, 16.f),   // upper-right
        Block(160.f, 160.f, 160.f, 16.f),   // top-left
        Block(480.f, 160.f, 160.f, 16.f),   // top-right
    };

    PhysicsEngine physics(WIDTH, HEIGHT);
    for (int i = 0; i < BLOCK_COUNT; i++)
        physics.addPlatform(&blocks[i]);

    InputManager input;

    bool fontOk = fontHeader.loadFromFile("SnowBrosAssets/Fonts/header-font.ttf");

    Text hudText;
    if (fontOk)
    {
        hudText.setFont(fontHeader);
        hudText.setCharacterSize(16);
        hudText.setFillColor(Color::White);
    }

    bool debugOn = false;

    RectangleShape bg(Vector2f(WIDTH, HEIGHT));
    bg.setFillColor(Color::Black);

    Clock clock;

    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();

        //Minimum requirement
        if (dt > 0.05f)
            dt = 0.05f;

        input.resetInput();

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            input.handleEvent(event);
        }

        if (input.debug())
            debugOn = !debugOn;
        if (input.gamePause())
            window.close();

        p1.handleInput(input, dt);
        p2.handleInput(input, dt);

        physics.update(p1, p2, dt);

        p1.update(dt);
        p2.update(dt);

        for (int i = 0; i < Player::MAX_BALLS; i++)
        {
            Snowball& b = p1.getBall(i);
            if (b.isActive() && p2.isAlive() && b.getHitbox().intersects(p2.getHitbox()))
            {
                p2.takeDamage();
                b.setActive(false);
            }
        }
        for (int i = 0; i < Player::MAX_BALLS; i++)
        {
            Snowball& b = p2.getBall(i);
            if (b.isActive() && p1.isAlive() && b.getHitbox().intersects(p1.getHitbox()))
            {
                p1.takeDamage();
                b.setActive(false);
            }
        }

        window.clear();
        window.draw(bg);

        for (int i = 0; i < BLOCK_COUNT; i++)
            blocks[i].draw(window, debugOn);

        p1.draw(window, debugOn);
        p2.draw(window, debugOn);

        if (fontOk)
        {
            hudText.setString(players[0].username + "  Lives:" + to_string(p1.getLives()) +
                "  Score:" + to_string(p1.getScore()));
            hudText.setPosition(8.f, 4.f);
            window.draw(hudText);

            hudText.setString(players[1].username + "  Lives:" + to_string(p2.getLives()) +
                "  Score:" + to_string(p2.getScore()));
            hudText.setPosition(8.f, 24.f);
            window.draw(hudText);

            hudText.setString("F1/H: hitboxes    ESC/P: quit");
            hudText.setPosition(8.f, HEIGHT - 24.f);
            window.draw(hudText);
        }

        window.display();
    }
}