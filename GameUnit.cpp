#include "GameUnit.h"

using namespace std;
using namespace sf;

const float GameUnit::WIDTH = 600;
const float GameUnit::HEIGHT = 600;

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

    Font font;
    bool fontOk = font.loadFromFile("SnowBrosAssets/Fonts/LEMONMILK-Regular.otf");

    Text hudText;
    if (fontOk)
    {
        hudText.setFont(font);
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
            hudText.setString("P1  Lives:" + to_string(p1.getLives()) +
                "  Score:" + to_string(p1.getScore()));
            hudText.setPosition(8.f, 4.f);
            window.draw(hudText);

            hudText.setString("P2  Lives:" + to_string(p2.getLives()) +
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