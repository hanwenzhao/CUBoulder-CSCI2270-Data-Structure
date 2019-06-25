#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>

using namespace std;

int loopCounter = 0;

struct itemArray
{
    string type;
    int price;
    int status;
};

void shiftArray(itemArray myArray[], int index, int numberofItems)
{
    for (int i = index; i <= numberofItems - 1; i++)
    {
        myArray[i] = myArray[i+1];
        loopCounter++;
    }
}

bool searchItem(itemArray myArray[], string line,int numberofItems)
{
    int cindex1 = line.find_first_of(',');
    int cindex2 = line.find_last_of(',');
    string searchType = line.substr(0,cindex1);
    int searchPrice = atoi(line.substr(cindex2+2,line.length()+1).c_str());
    int flag = -1;
    int searchStatus;
    if (line.substr(cindex1+2,cindex2-cindex1-2) == "for sale")
    {
        searchStatus = 1; //search for wanted
    }
    else if (line.substr(cindex1+2,cindex2-cindex1-2) == "wanted")
    {
        searchStatus = 0; //search for sales
    }
    for(int i = 0; i < numberofItems; i++)
    {
        if (searchStatus == 1)
        {
            if ((myArray[i].type == searchType) && (myArray[i].status == 1) && (myArray[i].price >= searchPrice))
            {
                cout<<myArray[i].type<<" "<<searchPrice<<endl;
                shiftArray(myArray, i, numberofItems);
                return true;
            }
            else
            {
                flag = 0;
            }
        }

        else if (searchStatus == 0)
        {
            if ((myArray[i].type == searchType) && (myArray[i].status == 0) && (myArray[i].price <= searchPrice))
            {
                cout<<myArray[i].type<<" "<<searchPrice<<endl;
                shiftArray(myArray, i, numberofItems);
                return true;
            }
            else
            {
                flag = 0;
            }
        }
        loopCounter++;
    }

    if (flag == 0)
    {
        return false;
    }
}


void addItem(itemArray myArray[], string line, int numberofItems)
{
    //cout<<"Adding Item"<<endl;
    //cout<<index<<endl;
    int cindex1 = line.find_first_of(',');
    int cindex2 = line.find_last_of(',');
    int index = numberofItems;
    //cout<<stoi(line.substr(cindex2+2,line.length()+1))<<endl;
    myArray[index].type = line.substr(0,cindex1);
    myArray[index].price = atoi(line.substr(cindex2+2,line.length()+1).c_str());
     if (line.substr(cindex1+2,cindex2-cindex1-2) == "for sale")
        {
            //cout<<"for sale"<<endl;
            myArray[index].status = 0;
        }
    else if (line.substr(cindex1+2,cindex2-cindex1-2) == "wanted")
        {
            //cout<<"wanted"<<endl;
            myArray[index].status = 1;
        }
}


int main(int argc, char *argv[])
{
    itemArray myArray[100];
    int numberofItems = 0;
    ifstream readFile;
    if (argc <= 1)
    {
        readFile.open("messageBoard.txt"); //debug
    }
    else
    {
        readFile.open(argv[1]);
    }
    //readFile.open("test.txt");
    string line;
    bool result;
    if (readFile.fail())
    {
        cout<<"Input file opening filed"<<endl;
    }
    else
    {
        while (!readFile.eof())
        {
            getline(readFile,line);
            if (line.empty())
            {
                break;
            }
            int cindex1 = line.find_first_of(',');
            int cindex2 = line.find_last_of(',');
            if (line.substr(cindex1+2,cindex2-cindex1-2) == "for sale" || line.substr(cindex1+2,cindex2-cindex1-2) == "wanted")
            {
                //cout<<"start searching for wanted"<<endl;
                //cout<<line.substr(cindex1+2,cindex2-cindex1-2)<<endl;
                result = searchItem(myArray, line, numberofItems);
                if (result == true)
                {
                    numberofItems = numberofItems - 1;
                }
                else if (result == false)
                {
                    //cout<<"Nothing Found"<<endl;
                    addItem(myArray, line, numberofItems);
                    numberofItems = numberofItems + 1;
                }
            }
            else
            {
                cout<<"Something is wrong"<<endl; //debug
            }
            loopCounter++;
        }
    }
    cout<<"#"<<endl;

    for (int i = 0; i <numberofItems; i++)
    {
        if (myArray[i].status == 0)
            {
                cout<<myArray[i].type<<", "<<"for sale"<<", "<<myArray[i].price<<endl;
            }
        else if (myArray[i].status == 1)
            {
                cout<<myArray[i].type<<", "<<"wanted"<<", "<<myArray[i].price<<endl;
            }
    }
    cout<<"#"<<endl;
    cout<<"loop iterations:"<<loopCounter<<endl;
    //readFile.close();
    return 0;
}
