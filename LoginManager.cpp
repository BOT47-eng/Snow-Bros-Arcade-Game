#include "LoginManager.hpp"

LoginManager::LoginManager() {
    loggedIn = false;
    currentScreen = LOGIN_SCREEN;
    activeField = 0;
    showPassword = false;
    inputUsername = "";
    inputPassword = "";
    inputEmail = "";
    statusMessage = "Welcome! Please Login";
}

void LoginManager::setFonts(Font& fontH, Font& fontN)
{
    fontHeader = fontH;
    fontNormal = fontN;
}

long long LoginManager::hash(const string& password) 
{
    long long hash = 5381;
    for (char strChar : password) 
    {
        hash = ((hash << 5) + hash) + strChar;
    }
    return hash;
}

bool LoginManager::verifyCredentials(string username, string password) 
{
    ifstream inFile("Resources/users.txt");
    PlayerInfo temp;
    long long inputHash = hash(password);

    while (getline(inFile, temp.username))
    { 
        inFile >> temp.passwordHash;
        inFile.ignore();
        getline(inFile, temp.email);
        getline(inFile, temp.created);

        cout << temp.username << endl;
        cout << temp.passwordHash << endl;
        cout << temp.email << endl;
        cout << temp.created << endl;

        if (string(temp.username) == username && temp.passwordHash == inputHash) 
        {
            currentUser = temp;
            return true;
        }
    }
    return false;
}

void LoginManager::saveUserToFile(PlayerInfo player)
{
    ofstream outFile("Resources/users.txt", ios::app);
    if (outFile.is_open()) 
    {
        //player.created has \n from ctime_s function
        outFile << player.username << "\n" << player.passwordHash << "\n" << player.email << "\n" << player.created;
    }
}

void LoginManager::logout() 
{
    cout << currentUser.username << " logged out" << endl;
    currentUser = PlayerInfo();
    loggedIn = false;
    currentScreen = LOGIN_SCREEN;
    inputUsername = ""; 
    inputPassword = "";
    inputEmail = "";
    statusMessage = "Welcome! Please Login";
}

void LoginManager::handleInput(Event& event, RenderWindow& window)
{
    if (event.type == Event::TextEntered)
    {
        if (event.text.unicode == 8)
        {
            if (activeField == 0 && !inputUsername.empty())
                inputUsername.pop_back();
            else if (activeField == 1 && !inputPassword.empty())
                inputPassword.pop_back();
            else if (activeField == 2 && !inputEmail.empty()) 
                inputEmail.pop_back();
        }
        else if (event.text.unicode < 128 && event.text.unicode > 31 && event.text.unicode != 32)
        {
            char tempChar = static_cast<char>(event.text.unicode);

            if (activeField == 0 && inputUsername.length() <= 17)
                inputUsername += tempChar;
            else if (activeField == 1 && inputPassword.length() <= 17)
                inputPassword += tempChar;
            else if (activeField == 2 && inputEmail.length() <= 30)
                inputEmail += tempChar;
        }
    }

    if (event.type == Event::MouseButtonPressed)
    {
        Vector2i mousePos = Mouse::getPosition(window);

        //Field buttons
        if (mousePos.y >= 150 && mousePos.y <= 190)
            activeField = 0;
        else if (mousePos.y >= 210 && mousePos.y <= 250)
            activeField = 1;
        else if (mousePos.y >= 270 && mousePos.y <= 310 && currentScreen == SIGNUP_SCREEN)
            activeField = 2;

        //Submit button
        if (mousePos.x >= 200 && mousePos.x <= 400 && mousePos.y >= 350 && mousePos.y <= 400)
        {
            bool nameTaken = usernameExists(inputUsername);

            if (inputUsername.length() == 0 || inputPassword.length() == 0)
            {
                statusMessage = "Invalid Credentials!";
                return;
            }

            if (inputUsername == "Guest")
            {
                statusMessage = "Cannot Use \"Guest\" Username!";
                return;
            }

            if (inputUsername == otherPlayer.username)
            {
                statusMessage = "Already Logged In!";
                return;
            }

            if (currentScreen == LOGIN_SCREEN)
            {
                if (!nameTaken)
                {
                    statusMessage = "No Existing Account!";
                    return;
                }

                if (verifyCredentials(inputUsername, inputPassword))
                {
                    loggedIn = true;
                    currentScreen = RETURN;
                }
                else
                {
                    statusMessage = "Invalid Credentials!";
                }
            }
            else
            {
                if (nameTaken)
                {
                    statusMessage = "Username Taken!";
                    return;
                }

                PlayerInfo newUser;
                newUser.username = inputUsername;
                newUser.passwordHash = hash(inputPassword);
                newUser.email = inputEmail;
                newUser.created = getTimestamp();
                saveUserToFile(newUser);
                statusMessage = "Signed up! Please Login";
                currentScreen = LOGIN_SCREEN;
            }
        }

        //Mask button
        if (mousePos.x >= 435 && mousePos.x <= 475 && mousePos.y >= 218 && mousePos.y <= 258) {
            showPassword = !showPassword;
        }

        //Option text
        if (mousePos.y >= 420 && mousePos.y <= 450)
        {
            if (currentScreen == LOGIN_SCREEN)
            {
                currentScreen = SIGNUP_SCREEN;
                statusMessage = "Signup Mode";
            }
            else
            {
                currentScreen = LOGIN_SCREEN;
                statusMessage = "Login Mode";
            }
        }
    }
}

void LoginManager::draw(RenderWindow& window) 
{
    if (currentScreen == RETURN) 
        return;

    RectangleShape verticalLine, horizontalLine;

    
    /*
        UI Debug Lines:
        verticalLine.setSize(Vector2f(1,600));
        verticalLine.setFillColor(Color::White);
        verticalLine.setPosition(Vector2f(300, 0));

        horizontalLine.setSize(Vector2f(1, 600));
        horizontalLine.setFillColor(Color::White);
        horizontalLine.setPosition(Vector2f(0, 300));
        horizontalLine.setRotation(-90);
    */
    

    window.draw(verticalLine);
    window.draw(horizontalLine);

    string titleText = "";

    if (currentScreen == LOGIN_SCREEN)
        titleText = "LOGIN";
    else
        titleText = "SIGNUP";

    Text title(titleText, fontHeader, 30);

    if (currentScreen == LOGIN_SCREEN)
        title.setPosition(240, 60);
    else
        title.setPosition(230, 60);

    
    window.draw(title);

    RectangleShape usernameContainer(Vector2f(250, 40));
    usernameContainer.setPosition(175, 150);

    if (activeField == 0)
        usernameContainer.setOutlineColor(Color::Cyan);
    else
        usernameContainer.setOutlineColor(Color::White);

    usernameContainer.setOutlineThickness(2);
    usernameContainer.setFillColor(Color(30, 30, 30));
    window.draw(usernameContainer);

    Text usernameLabel("Username", fontNormal, 40);
    usernameLabel.setPosition(175, 100);
    window.draw(usernameLabel);

    Text usernameText(inputUsername, fontNormal, 50);
    usernameText.setPosition(185, 127);
    window.draw(usernameText);

    RectangleShape passwordContainer(Vector2f(250, 40));
    passwordContainer.setPosition(175, 218);

    if (activeField == 1)
        passwordContainer.setOutlineColor(Color::Cyan);
    else
        passwordContainer.setOutlineColor(Color::White);
   
    passwordContainer.setOutlineThickness(2);
    passwordContainer.setFillColor(Color(30, 30, 30));
    window.draw(passwordContainer);

    Text passwordLabel("Password", fontNormal, 40);
    passwordLabel.setPosition(175, 168);
    window.draw(passwordLabel);

    string passwordTextStr = "";

    if (showPassword)
        passwordTextStr = inputPassword; 
    else
    {
        for (int i = 0; i < inputPassword.length(); i++)
            passwordTextStr += '*';
    }

    Text passwordText(passwordTextStr, fontNormal, 50);

    if (!showPassword)
    {
        passwordText.setPosition(185, 200);
    }
    else
    {
        passwordText.setPosition(185, 195);
    }

    window.draw(passwordText);

    //placeholder for eye icon
    RectangleShape maskContainer(Vector2f(40, 40));
    maskContainer.setPosition(435, 218);

    if (showPassword)
        maskContainer.setFillColor(Color::Green);
    else
        maskContainer.setFillColor(Color::Red);

    window.draw(maskContainer);

    if (currentScreen == SIGNUP_SCREEN) {
        RectangleShape emailContainer(Vector2f(400, 40));
        emailContainer.setPosition(100, 286);

        if (activeField == 2)
            emailContainer.setOutlineColor(Color::Cyan);
        else
            emailContainer.setOutlineColor(Color::White);

        emailContainer.setOutlineThickness(2);
        emailContainer.setFillColor(Color(30, 30, 30));
        window.draw(emailContainer);

        Text emailLabel("Email", fontNormal, 40);
        emailLabel.setPosition(100, 236);
        window.draw(emailLabel);

        Text emailText(inputEmail, fontNormal, 50);
        emailText.setPosition(110, 263);
        window.draw(emailText);
    }

    RectangleShape submitButton(Vector2f(200, 50));
    submitButton.setPosition(200, 350);
    submitButton.setFillColor(Color(70, 70, 180));
    window.draw(submitButton);

    Text submitButtonText("CONFIRM", fontHeader, 20);
    submitButtonText.setPosition(240, 360);
    window.draw(submitButtonText);

    string temp = "";

    if (currentScreen == LOGIN_SCREEN)
        temp = "No account? Sign Up";
    else
        temp = "Have account? Log In";

    RectangleShape optionContainer;
    optionContainer.setSize(Vector2f(600, 30));
    optionContainer.setPosition(Vector2f(0, 420));
    optionContainer.setFillColor(Color::Yellow);
    window.draw(optionContainer);

    Text optionText(temp, fontNormal, 50);
    
    if (currentScreen == LOGIN_SCREEN)
        optionText.setPosition(205, 392);
    else
        optionText.setPosition(201, 392);

    optionText.setFillColor(Color::Blue);
    window.draw(optionText);

    Text status(statusMessage, fontNormal, 60);

    if (statusMessage == "Login Mode")
    {
        status.setPosition(238, 450);
    }
    else if (statusMessage == "Signup Mode")
    {
        status.setPosition(233, 450);
    }
    else if (statusMessage == "Signed up! Please Login")
    {
        status.setPosition(175, 450);
    }
    else if (statusMessage == "Invalid Credentials!")
    {
        status.setPosition(190, 450);
    }
    else if (statusMessage == "Welcome! Please Login")
    {
        status.setPosition(175, 450);
    }
    else if (statusMessage == "Cannot Use \"Guest\" Username!")
    {
        status.setPosition(135, 450);
    }
    else if (statusMessage == "Already Logged In!")
    {
        status.setPosition(195, 450);
    }
    else if (statusMessage == "Username Taken!")
    {
        status.setPosition(205, 450);
    }
    else if (statusMessage == "No Existing Account!")
    {
        status.setPosition(187, 450);
    }
    else
    {
        status.setPosition(175, 450);
    }
    
    status.setFillColor(Color::Red);
    window.draw(status);
}

string LoginManager::getTimestamp() {
    time_t timestamp;
    time(&timestamp);
    char buffer[50];

    //This automatically adds has \n at the end 
   ctime_r(buffer, sizeof(buffer), &timestamp);

    string temp = buffer;

    return temp;
}

void LoginManager::setOtherPlayer(PlayerInfo other)
{
    otherPlayer = other;
}

bool LoginManager::usernameExists(const string& username)
{
    ifstream inFile("Resources/users.txt");
    if (!inFile.is_open())
        return false;

    PlayerInfo temp;
    while (getline(inFile, temp.username))
    {
        inFile >> temp.passwordHash;
        inFile.ignore();
        getline(inFile, temp.email);
        getline(inFile, temp.created);

        if (temp.username == username)
            return true;
    }
    return false;
}