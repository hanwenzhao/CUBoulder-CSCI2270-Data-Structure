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
    //cout << "delete all nodes" << endl;
    DeleteAll(root);
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

void MovieTree::printMovieInventory(MovieNode *node)
{
    if(node->leftChild != NULL)
    {
        printMovieInventory(node->leftChild);
    }
    cout<<"Movie: "<<node->title<<" "<<node->quantity<<endl;
    if(node->rightChild != NULL)
    {
        printMovieInventory(node->rightChild);
    }
}

void MovieTree::printMovieInventory()
{
    MovieNode *node = new MovieNode;
    node = root;
    printMovieInventory(node);
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
            if(foundMovie->quantity == 0)
            {
                deleteMovieNode(foundMovie->title);
            }
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

void MovieTree::DeleteAll(MovieNode *Node)
{
    MovieNode *tmp = new MovieNode;
    if(Node)
    {
        DeleteAll(Node->leftChild);
        DeleteAll(Node->rightChild);
        tmp = Node;
        cout<<"Deleting: "<<tmp->title<<endl;
        delete tmp;
    }
}

void MovieTree::deleteMovieNode(string title)
{
    //cout << "delete a move node: " << title << endl;
    bool found = false;
    MovieNode *current;
    MovieNode *parent;
    current = root;

    while(current)
    {
        if(current->title == title)
        {
            found = true;
            break;
        }
        else
        {
            parent = current;
            if(title > current->title)
            {
                current = current->rightChild;
            }
            else
            {
                current = current->leftChild;
            }
        }
    }

    if(found == false)
    {
        cout << "Movie not found." << endl;
        return;
    }

    //no children
    if((current->leftChild == NULL) && (current->rightChild == NULL))
    {
        if(parent->leftChild == current)
        {
            parent->leftChild = NULL;
        }
        else
        {
            parent->rightChild = NULL;
        }
        delete current;
        return;
    }

    //one children
    if(((current->leftChild != NULL) && (current->rightChild == NULL)) || ((current->leftChild == NULL) && (current->rightChild != NULL)))
    {
        if((current->leftChild != NULL) && (current->rightChild == NULL)) // has left child
        {
            if(parent->leftChild == current) // the node is a left child
            {
                parent->leftChild = current->leftChild;
                current->leftChild->parent = current->parent;
                delete current;
            }
            else // the node is a right child
            {
                parent->rightChild = current->leftChild;
                current->leftChild->parent = current->parent;
                delete current;
            }
        }

        else // has right child
        {
            if(parent->leftChild == current) // the node is a left child
            {
                parent->leftChild = current->rightChild;
                current->rightChild->parent = current->parent;
                delete current;
            }
            else // the node is a right child
            {
                parent->rightChild = current->rightChild;
                current->rightChild->parent = current->parent;
                delete current;
            }
        }
        return;
    }

    // has two children
    if((current->leftChild != NULL) && (current->rightChild != NULL))
    {
        MovieNode *min = treeMinimum(current->rightChild);
        // replacement is the right child
        if(current->rightChild == min)
        {
            if(current->parent->leftChild == current) // if node is a left child
            {
                current->parent->leftChild = min;
                min->parent = current->parent;
                current->leftChild->parent = min;
                min->leftChild = current->leftChild;
                delete current;
            }
            else
            {
                current->parent->rightChild = min;
                min->parent = current->parent;
                current->leftChild->parent = min;
                min->leftChild = current->leftChild;
                delete current;
            }
        }
        else // replacement is not the right child
        {
            if(current->parent->leftChild == current) // if the node is left child
            {
                min->parent->leftChild = min->rightChild;
                min->rightChild->parent = min->parent;
                min->parent = current->parent;
                current->parent->leftChild = min;
                min->leftChild = current->leftChild;
                min->rightChild = current->rightChild;
                current->rightChild->parent = min;
                current->leftChild->parent = min;
                delete current;
            }
            else
            {
                min->parent->leftChild = min->rightChild;
                min->rightChild->parent = min->parent;
                min->parent = current->parent;
                current->parent->rightChild = min;
                min->leftChild = current->leftChild;
                min->rightChild = current->rightChild;
                current->rightChild->parent = min;
                current->leftChild->parent = min;
                delete current;
            }
        }

    }
}

MovieNode* MovieTree::treeMinimum(MovieNode *node)
{
    while(node->leftChild != NULL)
    {
        node = node->leftChild;
    }
    return node;
}

void MovieTree::countMovieNodes(MovieNode *node, int *c)
{
    if(node)
    {
        if(node->leftChild != NULL)
        {
            countMovieNodes(node->leftChild, c);
        }
        (*c)++;
        if(node->rightChild != NULL)
        {
            countMovieNodes(node->rightChild, c);
        }
    }
}

int MovieTree::countMovieNodes()
{

    int numberofNodes = 0;
    int *counts = &numberofNodes;
    countMovieNodes(root, counts);
    //cout << numberofNodes << endl;
    return numberofNodes;
}
