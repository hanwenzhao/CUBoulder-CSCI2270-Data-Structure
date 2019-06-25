#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include "MovieTree.h"

using namespace std;

int main(int argc, char *argv[])
{
    ifstream readFile;
    MovieTree myMovieTree;
    string line;
    int ranking;
    string rk;
    string title;
    int year;
    string yr;
    int quantity;
    string qt;
    int input;
    string searchTitle;
    string rentTitle;
    string deleteTitle;
    int movieCount;
    if (argc <= 2)
    {
        readFile.open("Assignment6Movies.txt");
    }
    else
    {
        readFile.open(argv[1]);
    }
    if(readFile.fail())
    {
        cout << "Input file opening fail." << endl;
    }
    while(!readFile.eof())
    {
        while(getline(readFile,line))
        {
            stringstream ss(line);
            getline(ss, rk, ',');
            ranking = stoi(rk.c_str());
            getline(ss, title, ',');
            getline(ss, yr, ',');
            year = stoi(yr.c_str());
            getline(ss, qt, ',');
            quantity = stoi(qt.c_str());
            myMovieTree.addMovieNode(ranking, title, year, quantity);
        }
    }
    readFile.close();
    while(input != 6)
    {
        cout << "======Main Menu======" << endl;
        cout << "1. Find a movie" << endl;
        cout << "2. Rent a movie" << endl;
        cout << "3. Print the inventory" << endl;
        cout << "4. Delete a movie" << endl;
        cout << "5. Count the movies" << endl;
        cout << "6. Quit" << endl;
        cin >> input;

        if (input == 1)
        {
            cout << "Enter title:" << endl;
            while(true)
            {
                getline(cin, searchTitle);
                if (searchTitle != "")
                {
                    break;
                }
            }
            myMovieTree.findMovie(searchTitle);
        }

        if (input == 2)
        {
            cout << "Enter title:" << endl;
            while(true)
            {
                getline(cin, rentTitle);
                if (rentTitle != "")
                {
                    break;
                }
            }
            myMovieTree.rentMovie(rentTitle);
        }

        if (input == 3)
        {
            myMovieTree.printMovieInventory();
        }

        if (input == 4)
        {
            cout << "Enter title:" << endl;
            while(true)
            {
                getline(cin, deleteTitle);
                if (deleteTitle != "")
                {
                    break;
                }
            }
            myMovieTree.deleteMovieNode(deleteTitle);
        }

        if (input == 5)
        {
            cout<<"Tree contains: "<<myMovieTree.countMovieNodes()<<" movies." << endl;
        }
    }
    cout << "Goodbye!" << endl;
    return 0;
}
