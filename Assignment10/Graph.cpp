#include "Graph.h"
#include <vector>
#include <queue>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>

using namespace std;

Graph::Graph()
{

}

Graph::~Graph()
{
    //dtor
}

void Graph::readFileIntoGraph(Graph& g, char* fileName)
{
    vector<string> cities;
    ifstream in_stream;
    //cout << fileName << endl;
    in_stream.open(fileName);
    if (!in_stream)
    {
        cout << "Could not open file\n";
        return;
    }

    string city;
    string line;
    getline(in_stream,line);
    std::stringstream ss(line);
    int y = 0;

    // Read a list of cities from the first line
    while (getline(ss,city,','))
    {
        if (city != "cities")
        {
            g.addVertex(city);
            cities.push_back(city);
        }
    }

    // Now read in all the vertices
    int i = 0;
    string in;
    while (!in_stream.eof())
    {
        i = -1;
        getline(in_stream,line);
        stringstream ss(line); // why does ss.str(line) not work?

        while (getline(ss,in,','))
        {
            if (i == -1)
            {
                city = in;
            }
            else
            {
                if (in != "-1" && in != "0")
                {
                    g.addEdge(city,cities[i],atoi(in.c_str()));
                }
            }
            i++;
        }
    }
}

void Graph::addEdge(string v1, string v2, int weight)
{
    for(int i = 0; i < vertices.size(); i++)
    {
        if(vertices[i].name == v1)
        {
            for(int j = 0; j < vertices.size(); j++)
            {
                if(vertices[j].name == v2 && i != j)
                {
                    adjVertex av;
                    av.v = &vertices[j];
                    av.weight = weight;
                    vertices[i].adj.push_back(av);
                    /*
                    adjVertex av2;
                    av2.v = &vertices[i];
                    av2.weight = weight;
                    vertices[j].adj.push_back(av2);
                    */
                }
            }
        }
    }
}

void Graph::addVertex(string n)
{
    bool found = false;
    for(int i = 0; i < vertices.size(); i++)
    {
        if(vertices[i].name == n)
        {
            found = true;
            cout<<vertices[i].name<<" found."<<endl;
        }
    }
    if(found == false)
    {
        vertex v;
        v.name = n;
        v.district = -1;
        v.parent = NULL;
        vertices.push_back(v);
    }
}

void Graph::displayEdges()
{
    //loop through all vertices and adjacent vertices
    for(int i = 0; i < vertices.size(); i++)
    {
        cout << vertices[i].district << ":" << vertices[i].name<<"-->";
        for(int j = 0; j < vertices[i].adj.size(); j++)
        {
            cout<<vertices[i].adj[j].v->name;
            if (j != vertices[i].adj.size()-1)
            {
                cout<<"***";
            }
        }
        cout<<endl;
    }
}

void Graph::shortestPath(std::string startingCity,std::string endingCity)
{
    vertex *findStart = findVertex(startingCity);
    vertex *findEnd = findVertex(endingCity);
    if((findStart == NULL)||(findEnd == NULL))
    {
        cout << "One or more cities doesn't exist" << endl;
    }
    else if (findStart->district != findEnd->district)
    {
        cout << "No safe path between cities" << endl;
    }
    else if (findStart->district == -1)
    {
        cout << "Please identify the districts before checking distances" << endl;
    }
    else
    {
        vertex *myVertex = findVertex(startingCity);
        vertex *endCity = findVertex(endingCity);
        vertex *n = new vertex;
        vertex *edCity = new vertex;
        myVertex->visited = true;
        myVertex->distance = 0;
        queue<vertex *> *myQueue = new queue<vertex *>;
        myQueue->push(myVertex);
        //pathQueue->push(myVertex);
        while(!myQueue->empty())
        {
            n = myQueue->front();
            myQueue->pop();
            for(int x = 0; x < n->adj.size(); x++)
            {
                if(!n->adj[x].v->visited)
                {
                    n->adj[x].v->distance = n->distance + 1;
                    n->adj[x].v->parent = n;
                    //cout << n->adj[x].v->name << "'s parent is " << n->name << endl;
                    if(n->adj[x].v->name == endingCity)
                    {
                        edCity = n->adj[x].v;
                        //pathQueue->push(n->adj[x].v);
                        goto label;
                    }
                    else
                    {
                        n->adj[x].v->visited = true;
                        myQueue->push(n->adj[x].v);
                    }
                }
            }
        }
        label:
        //cout << "The distance is " << edCity->distance << endl;
        //cout << "The size of path is " << pathQueue->size() << endl;
        vertex *tmp = edCity;
        vertex *tmp2 = new vertex;
        vector<vertex *> *pathVector = new vector<vertex *>;
        cout << edCity->distance;
        while(tmp){
            pathVector->insert(pathVector->begin(), tmp);
            tmp = tmp->parent;
        }
        while(!pathVector->empty()){
            tmp2 = pathVector->front();
            pathVector->erase(pathVector->begin());
            cout << "," << tmp2->name;
        }
        cout << endl;
        /*
        while(!pathQueue->empty())
        {
            vertex *tmp = new vertex;
            tmp = pathQueue->front();
            pathQueue->pop();
            cout << "," << tmp->name;
        }
        cout << endl;
        */
        resetVisited();
    }
}

vertex * Graph::findVertex(string name)
{
    //cout << "finding city " << name << endl;
    for(int x = 0; x < vertices.size(); x++)
    {
        if (vertices[x].name == name)
        {
            return &vertices[x];
        }
    }
    return NULL;
}

void Graph::assignDistricts()
{
    currentID = 1;
    for(int i = 0; i < vertices.size(); i++)
    {
        if(!vertices[i].visited)
        {
            //cout << "Assign " << cities[i].name << " " << currentID << endl;
            BFTraversalLabel(vertices[i].name, currentID);
            currentID ++;
        }
    }
    resetVisited();
}

void Graph::BFTraversalLabel(string startingCity, int disID)
{
    vertex *myVertex = findVertex(startingCity);
    myVertex->visited = true;
    for(int x = 0; x < myVertex->adj.size(); x++)
    {
        if(myVertex->adj[x].v->district != -1)
        {
            disID = myVertex->adj[x].v->district;
            currentID --;
            break;
        }
    }
    myVertex->district = disID;
    //cout << "Assign " << myVertex->name << " " << "ID " << disID<< endl;
    for(int x = 0; x < myVertex->adj.size(); x++)
    {
        myVertex->adj[x].v->visited = true;
        myVertex->adj[x].v->district = disID;
        //cout << "Assign " << myVertex->adj[x].v->name << " " << "ID " << disID<< endl;
    }
}

void Graph::resetVisited()
{
    for(int i = 0; i < vertices.size(); i++)
    {
        vertices[i].visited = false;
    }
}
