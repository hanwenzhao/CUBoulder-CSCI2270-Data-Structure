#ifndef DUNGEONGAME_H
#define DUNGEONGAME_H

#include <iostream>

using namespace std;

struct player
{
    string playerName;
    int hp;
    int att;
    int def;
    bool sword;
    bool shield;
    player(string pname, int hitpoint, int attack, int defense)
    {
        playerName = pname;
        hp = hitpoint;
        att = attack;
        def = defense;
        sword = false;
        shield = false;
    }
};

struct Boss
{
    int hp;
    int att;
    int def;
    Boss(int hitpoint, int attack, int defense)
    {
        hp = hitpoint;
        att = attack;
        def = defense;
    }
    string apperance = " - - \n ･  ･  \n  ^  \n-| |- Ψ \n j l \n";
};

struct Guard
{
    int hp;
    int att;
    int def;
    Guard(int hitpoint, int attack, int defense)
    {
        hp = hitpoint;
        att = attack;
        def = defense;
    }
    string apperance = "  ▼_▼ \n   | ↗ \n  ' ' ";
};

struct location
{
    string locationName;
    location *prev;
    location *next;
    location(){};
    location(string name)
    {
        locationName = name;
        prev = NULL;
        next = NULL;
    }
};

class DungeonGame
{
private:
    string playerName;
    string currentLocation;
    location *head= new location("GATE");
    player *newPlayer = new player(playerName,100,20,10);
    Guard *newGuard = new Guard(60,40,10);
    Boss *newBoss = new Boss(120,60,20);
    bool fightGuard;
    bool fightBoss;
public:
    DungeonGame();
    ~DungeonGame();
    void setName(string playerName);
    void displayUI();
    void clearScreen();
    string getHead();
    string getApperance();
    void setLocation(string name);
    string getLocation();
    void addLocation(string name);
    void deleteLocation();
    void findSword();
    void findShield();
    void fightGuardSwitch();
    int *fightWithGuard();
    int getGuardHP();
    int getPlayerHP();
    bool passCorridor();
    void addHP();
    void fightBossSwitch();
    int *fightWithBoss();
    int getBossHP();
    void HappyEnding();
};

#endif // DUNGEONGAME_H
