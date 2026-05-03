#include "Shop.hpp"

using namespace std;
using namespace sf;

Shop::Shop()
{
    isExtraLifeChosen = false;
    isSpeedBoostChosen = false;
    isSnowBallPowerChosen = false;
    isDistanceIncreaseChosen = false;
    isBallonModeChosen = false;
    PurchaseState = "";
    r = g = b = 0;
    animationtime = 0.15f;
    speedofColorChanging = 0;
    currentime.restart();
    /*
        {353 , 28 , 88 , 133}
        {0 , 423 , 73 ,  74}
        {10 , 1057 , 63 , 76}
        {507 , 1233 , 43 , 43}
        {421 , 673 , 119 , 124}
    */
    ///// Loading the items 
    if (!itemsTextures[0].loadFromFile("Resources/SnowBrosAssets/Images/Items.png") ||
        !itemsTextures[1].loadFromFile("Resources/SnowBrosAssets/Images/Player_Blue.png") ||
        !itemsTextures[2].loadFromFile("Resources/SnowBrosAssets/Images/Player_Red.png"))
    {
        std::cout << "Error in loading the textures in Shop Class\n";
        exit(0);
    }
    if (!font.loadFromFile("Resources/SnowBrosAssets/Fonts/normal-font.ttf"))
    {
        std::cout << "Error in loading the fonts in Shop Class\n";
        exit(0);
    }
    if (!backgroundTex.loadFromFile("Resources/SnowBrosAssets/Images/ShopBackground.jpg"))
    {
        std::cout << "Error in loading the Background tex in Shop Class\n";
        exit(0);
    }

    for (int st = 0; st <= TOTAL_ITEMS - 1; st++)
    {
        cardstext[st].setFont(font);
        cardstext[st].setFillColor(sf::Color::Black);
        cardstext[st].setScale(1.2, 1.2);
    }
   
    itemsSprite[0].setTexture(itemsTextures[0]);
    itemsSprite[1].setTexture(itemsTextures[1]);
    itemsSprite[2].setTexture(itemsTextures[1]);
    itemsSprite[3].setTexture(itemsTextures[2]);
    itemsSprite[4].setTexture(itemsTextures[2]);

    itemsSprite[0].setTextureRect(IntRect({ 353, 28, 88, 133 }));
    itemsSprite[1].setTextureRect(IntRect({ 0, 423, 73, 74 }));
    itemsSprite[2].setTextureRect(IntRect({ 10, 1057, 63, 76 }));
    itemsSprite[3].setTextureRect(IntRect({ 507, 1233, 43, 43 }));
    itemsSprite[4].setTextureRect(IntRect({ 421, 673, 119, 124 }));

    // Setting Each Box Property 
    itemsSprite[0].setPosition(100, 100);
    itemsSprite[1].setPosition(400, 100);
    itemsSprite[2].setPosition(100, 250);
    itemsSprite[3].setPosition(400, 250);
    itemsSprite[4].setPosition(100, 400);

    itemsSprite[0].setScale({ 0.7 , 0.7 });
    itemsSprite[1].setScale({ 1.1 , 1.1 });
    itemsSprite[2].setScale({ 1.1 , 1.1 });
    itemsSprite[3].setScale({ 1.1 , 1.1 });
    itemsSprite[4].setScale({ 0.7 , 0.7 });

    cardstext[0].setString("Extra Life");
    cardstext[1].setString("Speed Boost");
    cardstext[2].setString("SnowBall Power");
    cardstext[3].setString("Distance+++");
    cardstext[4].setString("Ballon Time");


    Vector2f size = { 120 , 25 };
    for (int st = 0; st <= TOTAL_ITEMS - 1; st++)
    {
        cards[st].setSize(size);
        cards[st].setFillColor(sf::Color(100, 100, 100));
        cards[st].setPosition({ itemsSprite[st].getPosition().x - 13 , itemsSprite[st].getPosition().y + itemsSprite[st].getGlobalBounds().getSize().y + 20 });
        cardstext[st].setPosition({ cards[st].getPosition().x + 10 ,cards[st].getPosition().y - cards[st].getSize().y + 5 });
    }

    Heading.setFont(font);
    Heading.setString("Shop");
    Heading.setScale(3, 3);
    Heading.setPosition(265, -20);

    Vector2f texSize = { float(backgroundTex.getSize().x)  , float(backgroundTex.getSize().y) };
    Vector2f windowSize = { 600 , 600 };
    float ScaleX = (float)windowSize.x / texSize.x;
    float ScaleY = (float)windowSize.y / texSize.y;
    background.setTexture(backgroundTex);
    background.setScale(ScaleX, ScaleY);
}

void Shop::getExtraLife(Player& P)
{
    if (!P.getShopItem(0)) 
    {
        if (P.getGems() >= 50) 
        {
            P.addGems(-50);
            P.applyExtraLife();
            PurchaseState = "Successful";
        }
        else 
        {
            PurchaseState = "Not Enough Gems";
        }
    }
    else 
    {
        PurchaseState = "Already Purchased";
    }
}
void Shop::getSpeedBoost(Player& P)
{
    if (!P.getShopItem(3)) 
    {
        if (P.getGems() >= 20) 
        {
            P.addGems(-20);
            P.applySpeedBoost();
            PurchaseState = "Successful";
        }
        else 
        {
            PurchaseState = "Not Enough Gems";
        }
    }
    else {
        PurchaseState = "Already Purchased";
    }
}
void Shop::getSnowBall(Player& P)
{
    if (!P.getShopItem(1)) 
    {
        if (P.getGems() >= 30) 
        {
            P.addGems(-30);
            P.applySnowballPower();
            PurchaseState = "Successful";
        }
        else 
        {
            PurchaseState = "Not Enough Gems";
        }
    }
    else 
    {
        PurchaseState = "Already Purchased";
    }
}
void Shop::getDistanceIncrese(Player& P)
{
    if (!P.getShopItem(2)) 
    {
        if (P.getGems() >= 25) 
        {
            P.addGems(-25);
            P.applyDistanceIncrease();
            PurchaseState = "Successful";
        }
        else 
        {
            PurchaseState = "Not Enough Gems";
        }
    }
    else 
    {
        PurchaseState = "Already Purchased";
    }

}
void Shop::getBallonMode(Player& P)
{
    if (!P.getShopItem(4)) 
    {
        if (P.getGems() >= 35) 
        {
            P.addGems(-35);
            P.applyBalloonMode(30.f);
            PurchaseState = "Successful";
        }
        else 
        {
            PurchaseState = "Not Enough Gems";
        }
    }
    else
    {
        PurchaseState = "Already Purchased";
    }
}

// INSIDE UPDATE AFTER PLAYER CHOSES THE VALUE GETVALUE AND CHANGE THE PLAYER ATTRIBUTES  AND SET CHOSEN TO FALSE
void Shop::update(RenderWindow& window, Player& p)
{
    bool clicked = isMouseClicked();
    Vector2i pos = Mouse::getPosition(window);
    if (itemsSprite[0].getGlobalBounds().contains(float(pos.x), float(pos.y)) && clicked)
    {
        getExtraLife(p);
    }
    else if (itemsSprite[1].getGlobalBounds().contains(float(pos.x), float(pos.y)) && clicked)
    {
        getSpeedBoost(p);
    }
    else if (itemsSprite[2].getGlobalBounds().contains(float(pos.x), float(pos.y)) && clicked)
    {
        getSnowBall(p);
    }
    else if (itemsSprite[3].getGlobalBounds().contains(float(pos.x), float(pos.y)) && clicked)
    {
        getDistanceIncrese(p);
    }
    else if (itemsSprite[4].getGlobalBounds().contains(float(pos.x), float(pos.y)) && clicked)
    {
        getBallonMode(p);
    }
}


void Shop::draw(sf::RenderWindow& window, Player& p)
{
    update(window, p);

    window.draw(background);
    for (int st = 0; st <= TOTAL_ITEMS - 1; st++)
    {
        Vector2i pos = sf::Mouse::getPosition(window);
        if (itemsSprite[st].getGlobalBounds().contains(float(pos.x), float(pos.y)))
        {
            cards[st].setFillColor(sf::Color(r, g, b));
        }
        else
        {
            cards[st].setFillColor(sf::Color(100, 100, 100));
        }
    }
    for (int st = 0; st <= TOTAL_ITEMS - 1; st++)
    {
        window.draw(itemsSprite[st]);
        window.draw(cards[st]);
    }
    for (int st = 0; st <= TOTAL_ITEMS - 1; st++)
    {
        window.draw(cardstext[st]);
    }
    if (float(currentime.getElapsedTime().asSeconds()) >= animationtime)
    {
        r = (int)(std::sin(speedofColorChanging * 1.0f + 0.0f) * 127 + 128);
        g = (int)(std::sin(speedofColorChanging * 1.0f + 2.094f) * 127 + 128);
        b = (int)(std::sin(speedofColorChanging * 1.0f + 4.189f) * 127 + 128);
        speedofColorChanging += 0.05f;
        r %= 255;
        g %= 255;
        b %= 255;
        Heading.setFillColor(sf::Color(r, g, b));
        currentime.restart();
    }

    Text gemText("Gems: " + to_string(p.getGems()), font, 60);
    gemText.setFillColor(Color::White);
    gemText.setPosition(450.f, -10.f);
    window.draw(gemText);

    Text purchaseText(PurchaseState, font, 60);
    purchaseText.setFillColor(Color::White);
    purchaseText.setPosition(300.f, 480.f);
    window.draw(purchaseText);

    window.draw(Heading);
}
