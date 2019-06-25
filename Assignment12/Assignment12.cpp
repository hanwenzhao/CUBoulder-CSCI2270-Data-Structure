#include <iostream>
#include <string>
#include "HashTable.h"

using namespace std;

int main()
{
    int input;
    HashTable myHashTable;
    while(input != 5)
    {
        cout << "======Main Menu======" << endl;
        cout << "1. Insert movie" << endl;
        cout << "2. Delete movie" << endl;
        cout << "3. Find movie" << endl;
        cout << "4. Print table contents" << endl;
        cout << "5. Quit" << endl;
        cin >> input;

        if(input == 1)
        {
            string movieName;
            string movieYear;
            int intYear;
            cout << "Enter title:" << endl;
            while(true)
            {
                getline(cin, movieName);
                if (movieName != "")
                {
                    break;
                }
            }
            cout << "Enter year:" << endl;
            while(true)
            {
                getline(cin, movieYear);
                if (movieYear != "")
                {
                    break;
                }
            }
            intYear = stoi(movieYear);
            myHashTable.insertMovie(movieName, intYear);
        }

        if(input == 2)
        {
            string movieName;
            cout << "Enter title:" << endl;
            while(true)
            {
                getline(cin, movieName);
                if (movieName != "")
                {
                    break;
                }
            }
            myHashTable.deleteMovie(movieName);
        }

        if(input == 3)
        {
            string movieName;
            cout << "Enter title:" << endl;
            while(true)
            {
                getline(cin, movieName);
                if (movieName != "")
                {
                    break;
                }
            }
            myHashTable.findMovie(movieName);
        }

        if(input == 4)
        {
            myHashTable.printTableContents();
        }
    }
    cout << "Goodbye!" << endl;
    return 0;
}
