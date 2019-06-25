#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <ctime>
#include <cerrno>
#include <unistd.h>
#include <DungeonGame.h>

using namespace std;



int main()
{
    DungeonGame myGame;
    cout << "Welcome to the Dungeon Game!" << endl;
    sleep(1);
    cout << "Please enter your name: " << endl;
    string playerName;
    while(true)
    {
        getline(cin, playerName);
        if (playerName != "")
        {
            break;
        }
    }
    myGame.setName(playerName);
    cout << "Welcome " << playerName << "!" << endl;
    sleep(1);
    cout << "Now you are the savior from the Nowhere Kingdom." << endl;
    sleep(1);
    cout << "You need to recuse the princess from the Inferno." << endl;
    sleep(1);
    cout << "In the end of the Dungeon, there is a boss--The Dark One." << endl;
    sleep(1);
    cout << "You need to beat the Dark One.\n";
    cout << "and bring the princess back to the Kingdom." << endl;
    sleep(1);
    cout << "Press any key to continue..." << endl;
    cin.get();
    myGame.clearScreen();
    string input;
    // start the game
    while(true)
    {
        if(myGame.getLocation() == "GATE")
        {
label1:
            myGame.displayUI();
            cout << "You are in front of the gate of Inferno" << endl;
            sleep(1);
            cout << "Would you like to open the gate? (y/n)" << endl;
            while(true)
            {
                cin >> input;
                if(input == "y")
                {
                    myGame.setLocation("HALL");
                    myGame.addLocation("HALL");
                    myGame.clearScreen();
                    break;
                }
                else if(input == "n")
                {
                    myGame.setLocation("GAMEOVER");
                    myGame.clearScreen();
                    break;
                }
                else
                {
                    cout << "Please enter y for yes, n for no." << endl;
                    sleep(1);
                    myGame.clearScreen();
                    goto label1;
                }
            }
        }
        if(myGame.getLocation() == "HALL")
        {
label2:
            myGame.displayUI();
            cout << "Now you are in the big Hall of the Inferno." << endl;
            sleep(1);
            cout << "There are three doors in front of you." << endl;
            sleep(1);
            cout << "Would you like to go left(l), middle(m), right(r), or back(b)?" << endl;
            while(true)
            {
                cin >> input;
                if(input == "l")
                {
                    myGame.setLocation("SWORDROOM");
                    myGame.addLocation("SWORDROOM");
                    myGame.clearScreen();
                    break;
                }
                else if(input == "m")
                {
                    myGame.setLocation("SHIELDROOM");
                    myGame.addLocation("SHIELDROOM");
                    myGame.clearScreen();
                    break;
                }
                else if(input == "r")
                {
                    myGame.setLocation("CORRIDOR");
                    myGame.addLocation("CORRIDOR");
                    myGame.clearScreen();
                    break;
                }
                else if(input == "b")
                {
                    myGame.setLocation("GATE");
                    myGame.deleteLocation();
                    myGame.clearScreen();
                    break;
                }
                else
                {
                    cout << "Please enter l for left, m for middle, r for right, and b for back." << endl;
                    sleep(1);
                    myGame.clearScreen();
                    goto label2;
                }
            }
        }
        if(myGame.getLocation() == "SWORDROOM")
        {
            myGame.findSword();
label3:
            myGame.displayUI();
            cout << "This is the room where the Dark One stores his best sword." << endl;
            sleep(1);
            cout << "You find a decent sword named Excalibur." << endl;
            sleep(1);
            cout << "Would you like to go back(b)?" << endl;
            while(true)
            {
                cin>>input;
                if(input == "b")
                {
                    myGame.setLocation("HALL");
                    myGame.deleteLocation();
                    myGame.clearScreen();
                    break;
                }
                else
                {
                    cout << "Please enter b for back." << endl;
                    sleep(1);
                    myGame.clearScreen();
                    goto label3;
                }
            }
        }
        if(myGame.getLocation() == "SHIELDROOM")
        {
label4:
            myGame.fightGuardSwitch();
label5:
            myGame.displayUI();
            cout << "Now you are in the room where the Dark One stores his best shield--Aegis." << endl;
            sleep(1);
            cout << "However there is a guard in front of you." << endl;
            sleep(1);
            cout << "Would you like to fight the guard(f), or run back(b)?" << endl;
            while(true)
            {
                cin>>input;
                if(input == "f")
                {
                    int *damages = myGame.fightWithGuard();
                    int playerDamage = damages[0];
                    int guardDamge = damages[1];
                    cout << "You caused " << playerDamage << " damages to the Guard." << endl;
                    sleep(2);
                    cout << "The Guard caused " << guardDamge << " damages to you." << endl;
                    sleep(2);
                    myGame.clearScreen();
                    if(myGame.getGuardHP() <= 0)
                    {
                        myGame.fightGuardSwitch();
                        myGame.findShield();
                        myGame.clearScreen();
                        myGame.displayUI();
                        cout << "You have beaten the guard!" << endl;
                        sleep(1);
                        cout << "You find a decent shield--Aegis!" << endl;
                        sleep(1);
label6:
                        cout << "Would you like to go back(b)?" << endl;
                        while(true)
                        {
                            cin>>input;
                            if(input == "b")
                            {
                                myGame.setLocation("HALL");
                                myGame.deleteLocation();
                                myGame.clearScreen();
                                goto label2;
                            }
                            else
                            {
                                cout << "Please enter b to go back." << endl;
                                goto label6;
                            }
                        }
                    }
                    if(myGame.getPlayerHP() <= 0)
                    {
                        cout << "You died." << endl;
                        myGame.setLocation("GAMEOVER");
                        myGame.clearScreen();
                        goto label99;
                    }
                    else
                    {
                        goto label5;
                    }
                }
                else if(input == "b")
                {
                    myGame.setLocation("HALL");
                    myGame.fightGuardSwitch();
                    myGame.deleteLocation();
                    myGame.clearScreen();
                    break;
                }
                else
                {
                    cout << "Please enter f for fight, or b for back." << endl;
                    sleep(1);
                    myGame.clearScreen();
                    goto label5;
                }

            }
        }
        if(myGame.getLocation() == "CORRIDOR")
        {
label7:
            myGame.displayUI();
            cout << "Now you are in the corridor." << endl;
            sleep(1);
            cout << "On the wall it says, you need Excalibur and Aegis to pass here." << endl;
            sleep(1);
            cout << "Would you like to continue(y) or go back (b)?" << endl;
            while(true)
            {
                cin>>input;
                if(input == "y")
                {
                        myGame.setLocation("FIANLBOSS");
                        myGame.addLocation("FINALBOSS");
                        cout << "You find a bottle of potion in the corridor." << endl;
                        sleep(1);
                        cout << "It gives you extra 60 HP." << endl;
                        sleep(1);
                        myGame.addHP();
                        myGame.clearScreen();
                        break;
                }
                else if(input == "b")
                {
                    myGame.setLocation("HALL");
                    myGame.deleteLocation();
                    myGame.clearScreen();
                    break;
                }
                else
                {
                    cout << "Please enter y for continue, b for back." << endl;
                    sleep(1);
                    myGame.clearScreen();
                    goto label7;
                }
            }
        }
        if(myGame.getLocation() == "FIANLBOSS")
        {
            myGame.fightBossSwitch();
label8:
            while(true)
            {
                myGame.displayUI();
                cout << "Now you are facing the final enemy: The Dark One." << endl;
                sleep(1);
                cout << "Would you like to fight(f), or run back(b)?" << endl;
                cin>>input;
                if(input == "f")
                {
                    int *damages = myGame.fightWithBoss();
                    int playerDamage = damages[0];
                    int bossDamge = damages[1];
                    cout << "You caused " << playerDamage << " damages to The Dark One." << endl;
                    sleep(2);
                    cout << "The Dark One caused " << bossDamge << " damages to you." << endl;
                    sleep(2);
                    myGame.clearScreen();
                    if(myGame.getBossHP() <= 0)
                    {
                        myGame.fightBossSwitch();
                        myGame.clearScreen();
                        myGame.displayUI();
                        myGame.setLocation("HAPPYENDING");
                        break;
                    }
                    if(myGame.getPlayerHP() <= 0)
                    {
                        cout << "You died." << endl;
                        myGame.setLocation("GAMEOVER");
                        myGame.clearScreen();
                        goto label99;
                    }
                }
                else if(input == "b")
                {
                    myGame.setLocation("CORRIDOR");
                    myGame.fightBossSwitch();
                    myGame.deleteLocation();
                    myGame.clearScreen();
                    break;
                }
                else
                {
                    cout << "Please enter f to fight, b to go back." << endl;
                    sleep(1);
                    myGame.clearScreen();
                    goto label8;
                }
            }
        }
        if(myGame.getLocation() == "HAPPYENDING")
        {
            myGame.clearScreen();
            myGame.HappyEnding();
            cout << "Congratulation! You just beaten The Dark One!" << endl;
            sleep(1);
            cout << "You save the princess from the Inferno!" << endl;
            sleep(1);
            cout << "Thanks for playing!" << endl;
            sleep(1);
            break;
        }
label99:
        if(myGame.getLocation() == "GAMEOVER")
        {
            cout << "GAME OVER" << endl;
            cout << "Thanks for playing!" << endl;
            break;
        }
    }
    cout << "Good Bye!" << endl;
    return 0;
}
