#include "LeaderBoard.hpp"

using namespace std;
using namespace sf;

void Leaderboard::saveToFile(string name, int scores, int levelReached, string date)
{
    ofstream file;
    file.open("Resources/Leaderboard.txt", ios::app);
    if (!file.is_open())
    {
        std::cout << "Error in Opening the leaderboard.txt file\n";
        exit(0);
    }
    file << name << " " << scores << " " << levelReached << " " << date << std::endl;
    file.close();
}

int Leaderboard::countNoOfPlayers()
{
    int size = 0;
    ifstream file;
    file.open("Resources/Leaderboard.txt", ios::in);
    if (!file.is_open())
    {
        std::cout << "Error in Opening the leaderboard.txt file\n";
        exit(0);
    }
    string s;
    while (getline(file, s))
    {
        size++;
    }
    file.close();
    return size;
}
void Leaderboard::sortRanking()
{
    const int size = countNoOfPlayers();
    for (int st = 0; st <= size - 1; st++)
    {
        for (int st2 = 0; st2 <= size - st - 1; st2++)
        {
            if (st2 != size - 1 && scores[st2 + 1] > scores[st2])
            {

                int temp = scores[st2 + 1];
                scores[st2 + 1] = scores[st2];
                scores[st2] = temp;

                string tempString = playerNames[st2 + 1];
                playerNames[st2 + 1] = playerNames[st2];
                playerNames[st2] = tempString;

                temp = levels[st2 + 1];
                levels[st2 + 1] = levels[st2];
                levels[st2] = temp;

                tempString = dates[st2 + 1];
                dates[st2 + 1] = dates[st2];
                dates[st2] = tempString;

            }
        }
    }
    // for(int st = 0 ; st <= size - 1 ; st++)
    // {
    //     std::cout << playerNames[st] << " " << scores[st] << std::endl ;
    // }
}

void Leaderboard::loadFromFile()
{
    const int size = countNoOfPlayers();
    if (size == 0)
    {
        return;
    }
    playerNames = new string[size];
    scores = new int[size];
    levels = new int[size];
    dates = new string[size];
    ifstream file;
    file.open("Resources/Leaderboard.txt", ios::in);
    //Making sure start from top
    file.clear();
    file.seekg(0, ios::beg);
    if (!file.is_open())
    {
        std::cout << "Error in Opening the leaderboard.txt file\n";
        exit(0);
    }
    string s;
    int  a;
    int level;
    string date;
    int index = 0;
    while (index < size && (file >> s >> a >> level >> date))
    {
        playerNames[index] = s;
        scores[index] = a;
        levels[index] = level;
        dates[index] = date;
        index++;
    }
    sortRanking();
    file.close();
}

void Leaderboard::draw(sf::RenderWindow& window)
{
    sf::Event event;
    const int size = countNoOfPlayers();

    sf::Text title("TOP PLAYER RANKING", font, 80);
    title.setFillColor(sf::Color::Red);
    title.setPosition(125, -20);

    sf::Text labels("#      NAME                          SCORE   L    DATE", font, 60);
    labels.setFillColor(sf::Color::Blue);
    labels.setPosition(25, 45);

    while (window.pollEvent(event))
    {
        //if (event.type == sf::Event::MouseWheelScrolled)
        //{
        //    // To Prevent from going down too much
        //    if (!(view->getCenter().y - 300 <= 0)) // Mdipoint - 300 to get the pos of top of center 
        //    {
        //        view->move({ 0, -event.mouseWheelScroll.delta * 20.f });
        //    }
        //    else
        //    {
        //        view->move({ 0 ,  10 });
        //    }
        //}
    }
    //////// Adding the check weather userwants to go back or not
    if (sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        Vector2f pos = { float(sf::Mouse::getPosition(window).x) , float(sf::Mouse::getPosition(window).y) };
        if (GobackSprite.getGlobalBounds().contains(pos))
        {
            // Set back to default view of main menu
            View view({ 0 , 0 , 600 , 600 });
            window.setView(view);
            drawLeaderboard = false;
            return;
        }
    }

    window.setView(window.getDefaultView());
    window.draw(background);
    window.draw(GobackSprite);

    window.setView(*view);
    // Now i can draw everything under this view 

    window.draw(title);
    window.draw(labels);

    for (int i = 0; i < size && i < 10; i++)
    {
        float yPos = 100 + (i * 35);

        sf::Text txtRank(to_string(i + 1) + ".", font, 60);
        txtRank.setPosition(30, yPos);
        txtRank.setFillColor(sf::Color::White);

        sf::Text txtName(playerNames[i], font, 60);
        txtName.setPosition(80, yPos);
        txtName.setFillColor(sf::Color::White);

        sf::Text txtScore(to_string(scores[i]), font, 60);
        txtScore.setPosition(320, yPos);
        txtScore.setFillColor(sf::Color::White);

        sf::Text txtLevel(to_string(levels[i]), font, 60);
        txtLevel.setPosition(390, yPos);
        txtLevel.setFillColor(sf::Color::White);

        sf::Text txtDate(dates[i], font, 60);
        txtDate.setPosition(430, yPos);
        txtDate.setFillColor(sf::Color::White);

        if (i == 0) txtRank.setFillColor(sf::Color(255, 215, 0));
        else if (i == 1) txtRank.setFillColor(sf::Color(192, 192, 192));
        else if (i == 2) txtRank.setFillColor(sf::Color(205, 127, 50));

        window.draw(txtRank);
        window.draw(txtName);
        window.draw(txtScore);
        window.draw(txtLevel);
        window.draw(txtDate);
    }

    window.display();

}