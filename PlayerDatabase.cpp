#include "PlayerDatabase.hpp"
#include <iostream>
#include <ctime>
#include <sstream>

using namespace std;

PlayerDatabaseManager::PlayerDatabaseManager() 
{
    dataDirectory = "Resources/PlayerData/";
}

string PlayerDatabaseManager::getPlayerFilePath(const string& username) 
{
    return dataDirectory + username + ".txt";
}

bool PlayerDatabaseManager::fileExists(const string& filepath) 
{
    ifstream file(filepath);
    return file.is_open();
}

string PlayerDatabaseManager::getCurrentDateTime() 
{
    time_t timestamp;
    time(&timestamp);
    char buffer[50];

    //This automatically adds has \n at the end 
    ctime_s(buffer, sizeof(buffer), &timestamp);

    string temp = buffer;

    return temp;
}

bool PlayerDatabaseManager::savePlayerProgress(const PlayerSaveData& data, Leaderboard* ld)
{
    string filepath = getPlayerFilePath(data.username);
    ofstream file(filepath);

    if (!file.is_open()) 
    {
        cout << "Failed to open file for saving: " << filepath << endl;
        return false;
    }

    file << data.username << endl;
    file << data.current_level << endl;
    file << data.current_score << endl;
    file << data.lives_remaining << endl;
    file << data.gem_count << endl;
    file << data.high_score << endl;
    file << getCurrentDateTime();
    
    for (int i = 0; i < 5; i++)
    {
        file << data.shop_items[i];
        if (i < 4)
            file << " ";
    }

    file << endl;

    file.close();
    cout << "Player progress saved for: " << data.username << endl;

    if (ld)
    {
        ld->saveToFile(data.username, data.current_score, data.current_level, formatDate(data.last_updated));
    }

    return true;
}

bool PlayerDatabaseManager::loadPlayerProgress(const string& username, PlayerSaveData& data) 
{
    string filepath = getPlayerFilePath(username);

    if (!fileExists(filepath)) 
    {
        cout << "Save file not found for: " << username << endl;
        return false;
    }

    ifstream file(filepath);
    if (!file.is_open()) 
    {
        cout << "Failed to open file for loading: " << filepath << endl;
        return false;
    }

    string line;
    int lineIndex = 0;
    while (getline(file, line)) 
    {
        switch (lineIndex) 
        {
            case 0: 
                data.username = line; 
                break;
            case 1: 
                data.current_level = stoi(line); 
                break;
            case 2: 
                data.current_score = stoi(line); 
                break;
            case 3: 
                data.lives_remaining = stoi(line); 
                break;
            case 4: 
                data.gem_count = stoi(line);
                break;
            case 5: 
                data.high_score = stoi(line); 
                break;
            case 6: 
                data.last_updated = line; 
                break;
            case 7:
                stringstream stream(line);
                int item;
                for (int i = 0; i < 5; i++) 
                {
                    if (stream >> item)
                    {
                        if (item != 0)
                            data.shop_items[i] = true;
                        else
                            data.shop_items[i] = false;
                    }
                    else 
                    {
                        cout << "Could not load all shop items" << endl;
                        file.close();
                        return false;
                    }
                }
                break;
        }
        lineIndex++;
    }

    //cout << data.current_level << endl;

    file.close();
    cout << "Player progress loaded for: " << username << endl;
    return true;
}

bool PlayerDatabaseManager::playerSaveExists(const string& username) 
{
    return fileExists(getPlayerFilePath(username));
}

string PlayerDatabaseManager::formatDate(string date)
{
    stringstream ss(date);
    string dayName, monthName, time;
    int day, year;

    ss >> dayName >> monthName >> day >> time >> year;

    int month = 0;
    if (monthName == "Jan") 
        month = 1;
    else if (monthName == "Feb") 
        month = 2;
    else if (monthName == "Mar")
        month = 3;
    else if (monthName == "Apr") 
        month = 4;
    else if (monthName == "May") 
        month = 5;
    else if (monthName == "Jun")
        month = 6;
    else if (monthName == "Jul") 
        month = 7;
    else if (monthName == "Aug") 
        month = 8;
    else if (monthName == "Sep") 
        month = 9;
    else if (monthName == "Oct") 
        month = 10;
    else if (monthName == "Nov") 
        month = 11;
    else if (monthName == "Dec") 
        month = 12;

    int yearShort = year % 100; 

    stringstream result;
    result << (day < 10 ? "0" : "") << day << "/" << (month < 10 ? "0" : "") << month << "/" << (yearShort < 10 ? "0" : "") << yearShort;

    return result.str();
}