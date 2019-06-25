#include "HashTable.h"
#include <iostream>

HashTable::HashTable()
{
    //ctor
    for (int x = 0; x < tableSize; x++)
    {
        hashTable[x].next = NULL;
    }
}

HashTable::~HashTable()
{
    //dtor
}

int HashTable::hashSum(std::string key, int tableSize)
{
    int sum = 0;
    for(int i = 0; i < key.size(); i++)
    {
        sum = sum +key[i];
    }
    sum = sum % tableSize;
    return sum;
}

void HashTable::findMovie(std::string value)
{
    int index = hashSum(value, tableSize);
    HashElem *tmp = new HashElem;
    if(hashTable[index].next != NULL)
    {
        tmp = hashTable[index].next;
        while(tmp != NULL)
        {
            if(tmp->title == value)
            {
                std::cout << index << ":" << tmp->title << ":" << tmp->year << std::endl;
                return;
            }
            else
            {
                tmp = tmp->next;
            }
        }
    }
    else
    {
        std::cout << "not found" << std::endl;
        return;
    }
}

void HashTable::insertMovie(std::string name, int year)
{
    int index = hashSum(name, tableSize);
    HashElem *hashElement = new HashElem(name, year);
    hashElement->next = NULL;
    HashElem *tmp = new HashElem;
    //std::cout << "The index is " << index << std::endl;
    if(hashTable[index].next == NULL)
    {
        hashElement->previous = &hashTable[index];
        hashTable[index].next = hashElement;
    }
    else
    {
        //std::cout << "Adding next" << std::endl;
        tmp = hashTable[index].next;
        while(tmp->next != NULL)
        {
            tmp = tmp->next;
        }
        tmp->next = hashElement;
        hashElement->previous = tmp;
    }
}

void HashTable::deleteMovie(std::string name)
{
    int index = hashSum(name, tableSize);
    HashElem *tmp = new HashElem;
    if(hashTable[index].next != NULL)
    {
        tmp = hashTable[index].next;
        while(tmp != NULL)
        {
            if(tmp->title == name)
            {
                tmp->previous->next = tmp->next;
                if(tmp->next != NULL)
                {
                    tmp->next->previous = tmp->previous;
                }
                delete tmp;
                break;
            }
            tmp = tmp->next;
        }
    }
}

void HashTable::printTableContents()
{
    HashElem *tmp = new HashElem;
    bool Empty = isEmpty();
    if(Empty == true)
    {
        std::cout << "empty" << std::endl;
    }
    else
    {
        for(int x = 0; x < tableSize; x++)
        {
            if(hashTable[x].next != NULL)
            {
                tmp = hashTable[x].next;
                while(tmp != NULL)
                {
                    std::cout << tmp->title << ":" << tmp->year << std::endl;
                    tmp = tmp -> next;
                }
            }
        }
    }
}

bool HashTable::isEmpty()
{
    for(int x = 0; x < tableSize; x++)
    {
        if(hashTable[x].next != NULL)
        {
            return false;
        }
    }
    return true;
}




