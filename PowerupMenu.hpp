#pragma once
#include <SFML/Graphics.hpp>
#include "Player.hpp"

class PowerupMenu
{
private:
	sf::RectangleShape bg;
	sf::Text titleText;
	sf::Text option1Text;
	sf::Text option2Text;
	sf::Text option3Text;
	sf::RectangleShape box1;
	sf::RectangleShape box2;
	sf::RectangleShape box3;
	int selectedOption;
	bool isActive;

public:
	PowerupMenu(sf::Font& font)
	{
		selectedOption = 0;
		isActive = false;

		bg.setSize(sf::Vector2f(600, 600));
		bg.setFillColor(sf::Color::Black);

		titleText.setFont(font);
		titleText.setString("Choose a Powerup!");
		titleText.setCharacterSize(80);
		titleText.setFillColor(sf::Color::White);
		titleText.setPosition(170, 0);

		option1Text.setFont(font);
		option1Text.setString("1. Speed Boost (15s)");
		option1Text.setCharacterSize(50);
		option1Text.setFillColor(sf::Color::White);
		option1Text.setPosition(150, 170);

		option2Text.setFont(font);
		option2Text.setString("2. Snowball Power");
		option2Text.setCharacterSize(50);
		option2Text.setFillColor(sf::Color::White);
		option2Text.setPosition(150, 270);

		option3Text.setFont(font);
		option3Text.setString("3. Balloon Mode (15s)");
		option3Text.setCharacterSize(50);
		option3Text.setFillColor(sf::Color::White);
		option3Text.setPosition(150, 370);

		box1.setSize(sf::Vector2f(400, 60));
		box1.setPosition(100, 185);
		box1.setFillColor(sf::Color::Transparent);
		box1.setOutlineThickness(2);
		box1.setOutlineColor(sf::Color::Yellow);

		box2.setSize(sf::Vector2f(400, 60));
		box2.setPosition(100, 285);
		box2.setFillColor(sf::Color::Transparent);
		box2.setOutlineThickness(2);
		box2.setOutlineColor(sf::Color::White);

		box3.setSize(sf::Vector2f(400, 60));
		box3.setPosition(100, 385);
		box3.setFillColor(sf::Color::Transparent);
		box3.setOutlineThickness(2);
		box3.setOutlineColor(sf::Color::White);
	}

	void setActive(bool active)
	{
		isActive = active;
		selectedOption = 0;
		updateBoxColors();
	}

	bool getActive() const
	{
		return isActive;
	}

	void moveSelection(int direction)
	{
		selectedOption += direction;
		if (selectedOption < 0) 
			selectedOption = 2;
		if (selectedOption > 2) 
			selectedOption = 0;
		updateBoxColors();
	}

	int getSelectedOption() const
	{
		return selectedOption;
	}

	void updateBoxColors()
	{
		sf::Color active(0, 255, 0);
		sf::Color inactive(255, 255, 255);

		if (selectedOption == 0)
		{
			box1.setOutlineColor(active);
			box2.setOutlineColor(inactive);
			box3.setOutlineColor(inactive);
		}
		else if (selectedOption == 1)
		{
			box1.setOutlineColor(inactive);
			box2.setOutlineColor(active);
			box3.setOutlineColor(inactive);
		}
		else if (selectedOption == 2)
		{
			box1.setOutlineColor(inactive);
			box2.setOutlineColor(inactive);
			box3.setOutlineColor(active);
		}
	}

	void draw(sf::RenderWindow& window)
	{
		if (!isActive) 
			return;
		window.draw(bg);
		window.draw(box1);
		window.draw(box2);
		window.draw(box3);
		window.draw(titleText);
		window.draw(option1Text);
		window.draw(option2Text);
		window.draw(option3Text);
	}
};