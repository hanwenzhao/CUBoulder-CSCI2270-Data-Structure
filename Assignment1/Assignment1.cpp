#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

struct itemArray
{
    string type;
    int price;
    string status;
};
int main(int argc, char *argv[])
{
    itemArray myArray[100];
    ifstream readFile;
    string line;
    string type;
    string status;
    string sprice;
    int index;
    int price;
    int numberofItems = 0;
    int loopCounter = 0;
    bool found;
    if (argc <= 1)
    {
        //readFile.open("test.txt");
        readFile.open("messageBoard.txt");
    }
    else
    {
        readFile.open(argv[1]);
    }
    if (readFile.fail())
    {
        cout<<"Input file opening fail."<<endl;
    }
    else
    {
        while(getline(readFile,line))
        {
            if(line.empty())
            {
                break;
            }
            loopCounter++;
            //cout<<line<<endl;
            stringstream ss(line);
            getline(ss, type, ',');
            getline(ss, status, ',');
            status.erase(0,1);
            getline(ss, sprice, ',');
            price = stoi(sprice.erase(0,1));
            found = false;
            for ( int i = 0; i < numberofItems; i++)
            {
                loopCounter++;
                if (status == "for sale")
                {
                    if ((myArray[i].type == type) && (myArray[i].status == "wanted") && (myArray[i].price >= price))
                    {
                        cout<<type<<" "<<price<<endl;
                        index = i;
                        found = true;
                        break;
                    }
                }
                if (status == "wanted")
                {
                    if(myArray[i].type == type && myArray[i].status == "for sale" && myArray[i].price <= price)
                    {
                        cout<<type<<" "<<myArray[i].price<<endl;
                        index = i;
                        found = true;
                        break;
                    }
                }
            }

            if (found == true)
            {
                for(int i = index; i < numberofItems; i++)
                {
                    //cout<<"delete item"<<endl;
                    myArray[i] = myArray[i+1];
                    loopCounter++;
                }
                numberofItems--;
            }

            else if (found == false)
            {
                //cout<<"add item"<<endl;
                myArray[numberofItems].type = type;
                myArray[numberofItems].status = status;
                myArray[numberofItems].price = price;
                numberofItems++;
            }
        }
    }
    cout<<"#"<<endl;
    for (int i = 0; i < numberofItems; i++)
    {
        if (myArray[i].status == "for sale")
        {
            cout<<myArray[i].type<<", "<<"for sale"<<", "<<myArray[i].price<<endl;
        }
        else if (myArray[i].status == "wanted")
        {
            cout<<myArray[i].type<<", "<<"wanted"<<", "<<myArray[i].price<<endl;
        }
    }
    cout<<"#"<<endl;
    cout<<"loop iterations:"<<loopCounter<<endl;
    readFile.close();
    return 0;
}
