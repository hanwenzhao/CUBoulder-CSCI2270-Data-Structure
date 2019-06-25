#include "CommunicationNetwork.h"

using namespace std;

CommunicationNetwork::CommunicationNetwork(City *hd, City *tl)
{
    //ctor
    tail = tl;
    head = hd;
}

CommunicationNetwork::~CommunicationNetwork()
{
    //dtor
    //cout << "Destructors" << endl;
    deleteNetwork();
}

void CommunicationNetwork::addCity(std::string newCityName, std::string previousCity)
{
    if (previousCity == "First")
    {
        //cout<<"add city to first place"<<endl;
        City *newFirstCity = new City;
        newFirstCity->cityName = newCityName;
        newFirstCity->message = "";
        newFirstCity->next = head;
        newFirstCity->previous = NULL;
        head = newFirstCity;
    }
    else
    {
        City *tempCity = new City;
        City *tempCity2 = new City;
        City *newCity = new City;
        newCity->cityName = newCityName;
        newCity->message = "";
        newCity->next = NULL;
        newCity->previous = NULL;
        tempCity = head;
        while (tempCity)
        {
            if (tempCity->cityName == previousCity)
            {
                tempCity2 = tempCity->next;
                tempCity->next = newCity;
                newCity->next = tempCity2;
                newCity->previous = tempCity;
                newCity->next->previous = newCity;
                break;
            }
            tempCity = tempCity->next;
        }
    }
}

void CommunicationNetwork::deleteCity(std::string cityName)
{

    City *tempCity = new City;
    tempCity = head;
    bool found = false;
    //cout << "head is " << head->cityName << endl;
    while (tempCity != NULL)
    {
        if (cityName == tempCity->cityName)
        {
            found = true;
            //cout << "Found the city" << endl;
            break;
        }
        else
        {
            found = false;
        }
        tempCity = tempCity->next;
    }
    if (found == true)
    {
        if (cityName == head->cityName)
        {
            //cout << "delete the first city" << endl;
            tempCity = head;
            head = head->next;
            head->previous = NULL;
            delete tempCity;
        }
        else if (cityName == tail->cityName)
        {
            //cout << "delete the last city" << endl;
            //cout << "tail city is " << tail->cityName << endl;
            //cout << "The city before tail is " << tail->previous->cityName << endl;
            tempCity = tail;
            tail = tail->previous;
            tail->next = NULL;
            delete tempCity;
        }
        else
        {
            while (tempCity->cityName != cityName)
            {
                tempCity = tempCity->next;
            }
            tempCity->previous->next = tempCity->next;
            tempCity->next->previous = tempCity->previous;
            delete tempCity;
        }
    }
    else
    {
        cout << cityName << " not found" << endl;
    }
}

void CommunicationNetwork::transmitMsg(char *message)
{
    if (head != NULL)
    {
        head->message = message;
        City *tempCity = new City;
        tempCity = head;

        while (tempCity != NULL)
        {
            cout << tempCity->cityName << " received " << tempCity->message << endl;
            if (tempCity->next != NULL)
            {
                tempCity->next->message = tempCity->message;
                tempCity->message = "";
            }

            tempCity = tempCity->next;
        }
        tempCity = tail;
        tempCity->previous->message = tempCity->message;
        tempCity = tempCity->previous;
        while (tempCity != NULL)
        {
            cout << tempCity->cityName << " received " << tempCity->message << endl;
            if (tempCity->previous != NULL)
            {
                tempCity->previous->message = tempCity->message;
                tempCity->message = "";
            }

            tempCity = tempCity->previous;
        }
    }
    else
    {
        cout << "Empty list" << endl;
    }


}

void CommunicationNetwork::buildNetwork()
{
    string initialCities[10] = {"Los Angeles", "Phoenix", "Denver", "Dallas", "St. Louis", "Chicago", "Atlanta", "Washington, D.C.", "New York", "Boston"};

    City *cityNetwork = new City(initialCities[0], NULL, NULL, "");
    head = cityNetwork;
    tail = cityNetwork;
    City *curr = new City;

    for (int i = 1; i < 10; i++)
    {
        City *tempCity = new City;
        curr = head;
        tempCity->cityName = initialCities[i];
        tempCity->next = NULL;
        tempCity->previous = tail;
        tempCity->message = "";
        while (curr->next != NULL)
        {
            curr = curr->next;
        }
        curr->next = tempCity;
        tail = tempCity;
        //cout << "tail is " << tail->cityName << endl;
    }


    CommunicationNetwork::printNetwork();
}

void CommunicationNetwork::printNetwork()
{
    if (head == NULL)
    {

        cout << "===CURRENT PATH===" <<endl;
        cout << "NULL" << endl;
        cout << "==================" << endl;
    }
    else
    {
        City *curr = head;
        cout << "===CURRENT PATH===" <<endl;
        cout << "NULL <- ";
        while (curr->cityName != tail->cityName)
        {
            cout << curr->cityName << " <-> ";
            curr = curr->next;
        }
        cout << curr->cityName << " -> ";
        cout << "NULL" << endl;
        cout << "==================" << endl;
    }

}

void CommunicationNetwork::deleteNetwork()
{
    City *tempCity = new City;
    tempCity = head;
    while (tempCity)
    {
        cout << "deleting " << tempCity->cityName << endl;
        delete head;
        tempCity = tempCity->next;
        head = head->next;
    }
    head = NULL;
}
