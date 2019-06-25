#include <iostream>
#include <sstream>
#include "Queue.h"

using namespace std;

int main()
{
    int input;
    string word;
    Queue myQueue(10);
    while (input != 5)
    {
        cout << "======Main Menu=====" << endl;
        cout << "1. Enqueue word" << endl;
        cout << "2. Dequeue word" << endl;
        cout << "3. Print queue" << endl;
        cout << "4. Enqueue sentence" << endl;
        cout << "5. Quit" << endl;
        cin >> input;

        if (input == 1)
        {
            cout << "word: ";
            cin >> word;
            myQueue.enqueue(word);
        }

        if (input == 2)
        {
            myQueue.dequeue();
        }

        if (input == 3)
        {
            myQueue.printQueue();
        }

        if (input == 4)
        {
            cout << "sentence: ";
            cin.ignore();
            string line;
            getline(cin,line);
            stringstream ss(line);
            while(!ss.eof())
            {
                string tmp;
                ss >> tmp;
                myQueue.enqueue(tmp);
            }
        }
    }
    cout << "Goodbye!" << endl;
    return 0;
}
