#include "MovieTree.h"
#include <iostream>

using namespace std;

MovieTree::MovieTree()
{
    //ctor
    root = NULL;
}

MovieTree::~MovieTree()
{
    //dtor
}

void MovieTree::addMovieNode(int ranking, std::string title, int releaseYear, int quantity)
{
    //create a movie node
    //cout << "adding movie" << endl;
    MovieNode *newMovie = new MovieNode(ranking, title, releaseYear, quantity);
    newMovie->parent = NULL;
    newMovie->leftChild = NULL;
    newMovie->rightChild = NULL;
    MovieNode *temp = new MovieNode;
    MovieNode *parent = new MovieNode;
    //find the location for new node
    temp = root;
    parent = NULL;
    while(temp != NULL)
    {
        parent = temp;
        if(newMovie->title < temp->title)
        {
            temp = temp->leftChild;
        }
        else
        {
            temp = temp->rightChild;
        }
    }
    if(parent == NULL)
    {
        root = newMovie;
    }
    else if (newMovie->title < parent->title)
    {
        parent->leftChild = newMovie;
        newMovie->parent = parent;
    }
    else
    {
        parent->rightChild = newMovie;
        newMovie->parent = parent;
    }
}

void MovieTree::printNode(MovieNode *node)
{
    if(node->leftChild != NULL)
    {
        printNode(node->leftChild);
    }
    cout<<"Movie: "<<node->title<<" "<<node->quantity<<endl;
    if(node->rightChild != NULL)
    {
        printNode(node->rightChild);
    }
}

void MovieTree::printMovieInventory()
{
    MovieNode *node = new MovieNode;
    node = root;
    printNode(node);
}

MovieNode* MovieTree::search(string searchTitle)
{
    MovieNode *node = new MovieNode;
    node = root;
    while(node != NULL)
    {
        if(node->title > searchTitle)
        {
            node = node->leftChild;
        }
        else if (node->title < searchTitle)
        {
            node = node->rightChild;
        }
        else
        {
            return node;
        }
    }
    return NULL;
}

void MovieTree::findMovie(string title)
{
    MovieNode *foundMovie = new MovieNode;
    foundMovie = search(title);
    if(foundMovie != NULL)
    {
        cout << "Movie Info:" << endl;
        cout << "===========" << endl;
        cout << "Ranking:" << foundMovie->ranking << endl;
        cout << "Title:" << foundMovie->title << endl;
        cout << "Year:" << foundMovie->year << endl;
        cout << "Quantity:" << foundMovie->quantity << endl;
    }
    else
    {
        cout << "Movie not found." << endl;
    }
}

void MovieTree::rentMovie(string title)
{
    MovieNode *foundMovie = new MovieNode;
    foundMovie = search(title);
    if(foundMovie != NULL)
    {
        if (foundMovie->quantity != 0)
        {
            cout << "Movie has been rented." << endl;
            foundMovie->quantity--;
            cout << "Movie Info:" << endl;
            cout << "===========" << endl;
            cout << "Ranking:" << foundMovie->ranking << endl;
            cout << "Title:" << foundMovie->title << endl;
            cout << "Year:" << foundMovie->year << endl;
            cout << "Quantity:" << foundMovie->quantity << endl;
        }
        else
        {
            cout << "Movie out of stock." << endl;
        }

    }
    else
    {
        cout << "Movie not found." << endl;
    }
}
