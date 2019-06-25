#include <iostream>
#include "Graph.h"

using namespace std;

int main(int argc, char *argv[])
{
    int input;
    Graph myGraph;
    if(argc <= 2)
    {
        myGraph.readFileIntoGraph(myGraph,"zombieCities.txt");
    }
    else
    {
        myGraph.readFileIntoGraph(myGraph,argv[1]);
    }
    /*
    myGraph.addVertex("Boston");
    myGraph.addVertex("Boulder");
    myGraph.addVertex("Chicago");
    myGraph.addEdge("Boston", "Boulder", 2000);
    myGraph.addEdge("Boston", "Chicago", 982);
    */
    while(input != 4)
    {
        cout << "======Main Menu======" << endl;
        cout << "1. Print vertices" << endl;
        cout << "2. Find districts" << endl;
        cout << "3. Find shortest path" << endl;
        cout << "4. Quit" << endl;
        cin >> input;

        if(input == 1)
        {
            myGraph.displayEdges();
        }

        if(input == 2)
        {
            myGraph.assignDistricts();
        }

        if(input == 3)
        {
            string startingCity;
            string endingCity;
            cout <<	"Enter a starting city:" << endl;
            while(true)
            {
                getline(cin, startingCity);
                if (startingCity != "")
                {
                    break;
                }
            }
            cout << "Enter an ending city:" << endl;
            while(true)
            {
                getline(cin, endingCity);
                if (endingCity != "")
                {
                    break;
                }
            }
            myGraph.shortestPath(startingCity, endingCity);
        }
    }
    cout << "Goodbye!" << endl;
    return 0;
}
