#pragma once

#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <ctime>

#include "PlayerInfo.hpp"

class LoginManager {
private:
    //State variables to check which screen Player is on
    static const int LOGIN_SCREEN = 0;
    static const int SIGNUP_SCREEN = 1;
    static const int RETURN = 2;

    PlayerInfo currentUser;
    bool loggedIn;
    int currentScreen;
    bool showPassword;
    sf::Font fontHeader, fontNormal;

    //0 = Username, 1 = Password, 2 = Email
    int activeField;

    std::string inputUsername;
    std::string inputPassword;
    std::string inputEmail;
    std::string statusMessage;

    PlayerInfo otherPlayer;

    long long hash(const std::string& password);
    std::string getTimestamp();
    void saveUserToFile(PlayerInfo player);
    bool verifyCredentials(std::string username, std::string password);
    bool usernameExists(const std::string& username);

public:
    LoginManager();
    void handleInput(sf::Event& event, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    void setFonts(sf::Font& fontH, sf::Font& fontN);

    bool isLoggedIn() const 
    { 
        return loggedIn;
    }
    PlayerInfo getCurrentUser() const 
    { 
        return currentUser;
    }

    void logout(); 
    void setOtherPlayer(PlayerInfo other);

};