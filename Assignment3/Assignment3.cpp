//CSCI 2270
//Hanwen Zhao
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <stdlib.h>
#include "CommunicationNetwork.h"

using namespace std;

int main()
{
    int input;
    CommunicationNetwork cn1(NULL,NULL);
    ifstream readFile;
    string line;
    while (input != 6)
    {
        cout << "======Main Menu======" << endl;
        cout << "1. Build Network" << endl;
        cout << "2. Print Network Path" << endl;
        cout << "3. Transmit Message Coast-To-Coast" << endl;
        cout << "4. Add City" << endl;
        cout << "5. Delete City" << endl;
        cout << "6. Quit" << endl;

        cin >> input;
        if (input == 1)
        {
            cn1.buildNetwork();
        }
        if (input == 2)
        {

            cn1.printNetwork();
        }
        if (input == 3)
        {
            readFile.open("messageIn.txt");
            if (readFile.fail())
            {
                cout<<"Input file opening fail."<<endl;
            }
            else
            {
                while(!readFile.eof())
                {
                    getline(readFile, line, ' ');
                    //line.erase(remove_if(line.begin(), line.end(), ::ispunct), line.end());
                    line.erase(remove_if(line.begin(), line.end(), (int(*)(int))isspace), line.end());
                    char * mesg = new char [line.length()+1];
                    strcpy (mesg, line.c_str());
                    cn1.transmitMsg(mesg);

                }
            }
        }
        if (input == 4)
        {
            string cityNew;
            string cityPrevious;
            cout <<	"Enter a city name: " << endl;
            //cin >> cityNew;
            while(true)
            {
                getline(cin, cityNew);
                if (cityNew != "")
                {
                    break;
                }
            }
            //cout << "New city name is: " << cityNew <<endl;
            cout << "Enter a previous city name: " << endl;
            //cin >> cityPrevious;
            while(true)
            {
                getline(cin, cityPrevious);
                if (cityPrevious != "")
                {
                    break;
                }
            }
            cn1.addCity(cityNew, cityPrevious);
        }
        if (input == 5)
        {
            string cityDel;
            cout <<	"Enter a city name: " << endl;
            while(true)
            {
                getline(cin, cityDel);
                if (cityDel != "")
                {
                    break;
                }
            }
            cn1.delCity(cityDel);
        }
    }

    cout << "Goodbye!" << endl;
    exit(0);
    return 0;
}
