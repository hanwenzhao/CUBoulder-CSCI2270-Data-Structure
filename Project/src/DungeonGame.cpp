#include "DungeonGame.h"

DungeonGame::DungeonGame()
{
    //ctor
    currentLocation = "GATE";
    fightGuard = false;
    fightBoss = false;
}

DungeonGame::~DungeonGame()
{
    //dtor
}

void DungeonGame::setName(string plName)
{
    playerName = plName;
}

void DungeonGame::displayUI()
{

    cout << "============================Dungeon Game========================================" << endl;
    cout << "Current Location: ";
    location *tmp = head;
    while(tmp != NULL)
    {
        cout << tmp->locationName << "->";
        tmp = tmp->next;
    }
    cout << endl;
    if((fightGuard == true)&&(newGuard->hp > 0))
    {
        cout << "HP: " << newGuard->hp << endl;
        cout << "Attack: " << newGuard->att << endl;
        cout << "Defense: " << newGuard->def << endl;
        cout << newGuard->apperance << endl;
        cout << endl;
    }
    if(fightBoss == true)
    {
        cout << "HP: " << newBoss->hp << endl;
        cout << "Attack: " << newBoss->att << endl;
        cout << "Defense: " << newBoss->def << endl;
        cout << newBoss->apperance << endl;
        cout << endl;
    }
    cout << getApperance() << endl;
    cout << "HP: " << newPlayer->hp << endl;
    cout << "Attack: " << newPlayer->att << endl;
    cout << "Defense: " << newPlayer->def << endl;
    cout << "===============================================================================" << endl;
}

string DungeonGame::getHead()
{
    return head->locationName;
}

void DungeonGame::clearScreen()
{
    cout << string(100, '\n');
}

string DungeonGame::getApperance()
{
    if((newPlayer->sword == true) && (newPlayer->shield == false))
    {
        return "  (o-o) \n  |   | ∝╬▅▆▇◤ \n   ' ' ";
    }
    else if((newPlayer->sword == false) && (newPlayer->shield == true))
    {
        return "  (o-o) \n▊▊|   |  \n   ' ' ";
    }
    else if ((newPlayer->sword == true) && (newPlayer->shield == true))
    {
        return "  (o-o) \n▊▊|   | ∝╬▅▆▇◤ \n   ' ' ";
    }
    else
    {
        return "  (o-o) \n  |   | \n   ' ' ";
    }
}

void DungeonGame::setLocation(string locationName)
{
    currentLocation = locationName;
}

string DungeonGame::getLocation()
{
    return currentLocation;
}

void DungeonGame::addLocation(string name)
{
    location *newLocation = new location(name);
    location *tmp = head;
    while(tmp->next != NULL)
    {
        tmp = tmp->next;
    }
    newLocation->prev = tmp;
    tmp->next = newLocation;
    //cout << "location added" << endl;
}

void DungeonGame::deleteLocation()
{
    location *tmp = head;
    while(tmp->next != NULL)
    {
        tmp = tmp->next;
    }
    tmp->prev->next = NULL;
    delete tmp;
}

void DungeonGame::findSword()
{
    newPlayer->sword = true;
    newPlayer->att += 30;
}

void DungeonGame::fightGuardSwitch()
{
    if(fightGuard == false)
    {
        fightGuard = true;
    }
    else
    {
        fightGuard = false;
    }
}

int *DungeonGame::fightWithGuard()
{
    int playerDamage = newPlayer->att - newGuard->def;
    int guardDamage = newGuard->att - newPlayer->def;
    newPlayer->hp -= guardDamage;
    newGuard->hp -= playerDamage;
    int damages[] = {playerDamage, guardDamage};
    return damages;
}

int DungeonGame::getGuardHP()
{
    return newGuard->hp;
}

void DungeonGame::findShield()
{
    newPlayer->shield = true;
    newPlayer->def += 30;
}

int DungeonGame::getPlayerHP()
{
    return newPlayer->hp;
}

bool DungeonGame::passCorridor()
{
    if((newPlayer->sword == true) && (newPlayer->shield == true))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void DungeonGame::addHP()
{
    newPlayer->hp += 60;
}

void DungeonGame::fightBossSwitch()
{
    if(fightBoss == false)
    {
        fightBoss = true;
    }
    else
    {
        fightBoss = false;
    }
}

int *DungeonGame::fightWithBoss()
{
    int playerDamage = newPlayer->att - newBoss->def;
    int bossDamage = newBoss->att - newPlayer->def;
    newPlayer->hp -= bossDamage;
    newBoss->hp -= playerDamage;
    int damages[] = {playerDamage, bossDamage};
    return damages;
}

int DungeonGame::getBossHP()
{
    return newBoss->hp;
}

void DungeonGame::HappyEnding()
{
    cout << "============================Dungeon Game========================================" << endl;
    cout << "Current Location: ";
    location *tmp = head;
    while(tmp != NULL)
    {
        cout << tmp->locationName << "->";
        tmp = tmp->next;
    }
    cout << endl;
    cout << "  (o-o)   (o-o)\n";
    cout << "  |   |    | | \n";
    cout << "   ' '     ' ' " << endl;
    cout << "===============================================================================" << endl;
}
