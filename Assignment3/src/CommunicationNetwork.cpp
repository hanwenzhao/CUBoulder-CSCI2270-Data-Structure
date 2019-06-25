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
        tempCity = head;
        while (tempCity)
        {
            if (tempCity->cityName == previousCity)
            {
                tempCity2 = tempCity->next;
                tempCity->next = newCity;
                newCity->next = tempCity2;
                break;
            }
            tempCity = tempCity->next;
        }
    }
}

void CommunicationNetwork::delCity(std::string cityName)
{
    if (cityName == head->cityName)
    {
        City *tempCity = new City;
        tempCity = head;
        head = head->next;
        delete tempCity;
    }
    else
    {

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
    }
    else
    {
        cout << "Empty list" << endl;
    }


}

void CommunicationNetwork::buildNetwork()
{
    string initialCities[10] = {"Los Angeles", "Phoenix", "Denver", "Dallas", "St. Louis", "Chicago", "Atlanta", "Washington, D.C.", "New York", "Boston"};

    City *cityNetwork = new City(initialCities[0], NULL, "");
    head = cityNetwork;
    tail = cityNetwork;

    for (int i = 1; i < 10; i++)
    {
        City *tempCity = new City;
        City *curr = head;
        tempCity->cityName = initialCities[i];
        tempCity->next = NULL;
        tempCity->message = "";
        while (curr->next != NULL)
        {
            curr = curr->next;
        }
        curr->next = tempCity;
        tail = curr->next;
    }


    CommunicationNetwork::printNetwork();
}

void CommunicationNetwork::printNetwork()
{
    City *curr = head;
    cout << "===CURRENT PATH===" <<endl;
    while (curr)
    {
        cout << curr->cityName << " -> ";
        curr = curr->next;
    }
    cout << "NULL" << endl;
    cout << "==================" << endl;
}


