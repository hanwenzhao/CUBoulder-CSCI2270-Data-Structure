#ifndef GRAPH_H
#define GRAPH_H
#include<vector>
#include<iostream>

struct vertex;

/*This is the struct for the adjacent vertices for each
 vertex in the graph. */
struct adjVertex{
    vertex *v;
    int weight;
};
/*this is the struct for each vertex in the graph.
You will need a vector of these things.
When you construct the shortest path between two vertices, there
 are multiple approaches. There is an algorithm in your book that
 uses an array and the index in the array represents the order that
 the vertex with a specified ID is visited. In the struct vertex, the
 ID property is used for that algorithm. Another approach is to store
 a pointer to the parent vertex. I've added a property parent to struct
 vertex that can be used for that purpose.
 */
struct vertex{
    int ID;
    vertex *parent;
    std::string name;
    int district;
    bool visited;
    int distance;
    std::vector<adjVertex> adj;
};
/*Another approach to storing the shortest path is to store a vector of
 pointers to the vertices visited so far along the current path. You can
 use this struct queueVertex for that purpose. Truthfully, storing the parent
 for each vertex as mentioned above is probably easier.*/
struct queueVertex{
    int distance;
    std::vector<vertex *> path;
};
class Graph
{
    public:
        Graph();
        ~Graph();
        void addEdge(std::string v1, std::string v2, int weight);
        void addVertex(std::string name);
        void displayEdges();
        void assignDistricts();
        void shortestPath(std::string startingCity, std::string endingCity);
        void readFileIntoGraph(Graph& g, char* fileName);
    protected:
    private:
        std::vector<vertex> vertices;
        std::vector<vertex> cities;
        vertex * findVertex(std::string name);
        //call this from within assignDistricts to label the districts.
        //This method should implement a breadth first traversal from the startingCity
        //and assign all cities encountered the distID value
        void BFTraversalLabel(std::string startingCity, int distID);
        void resetVisited();
        int currentID;

};

#endif // GRAPH_H
