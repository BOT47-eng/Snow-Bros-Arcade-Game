#pragma once

#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <ctime>

#include "PlayerInfo.hpp"

using namespace std;
using namespace sf;

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
    Font fontHeader, fontNormal;

    //0 = Username, 1 = Password, 2 = Email
    int activeField;

    string inputUsername;
    string inputPassword;
    string inputEmail;
    string statusMessage;

    PlayerInfo otherPlayer;

    long long hash(const string& password);
    string getTimestamp();
    void saveUserToFile(PlayerInfo player);
    bool verifyCredentials(string username, string password);
    bool usernameExists(const string& username);

public:
    LoginManager();
    void handleInput(Event& event, RenderWindow& window);
    void draw(RenderWindow& window);
    void setFonts(Font& fontH, Font& fontN);

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