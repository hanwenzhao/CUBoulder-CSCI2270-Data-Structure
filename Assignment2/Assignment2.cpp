#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

struct topWords
{
    string word;
    int counts;
};

bool sortByCounts(const topWords &lhs, const topWords &rhs)
{
    return lhs.counts > rhs.counts;
}

topWords *ArrayDynamicAllocation(topWords inputArray[], int n)
{
    topWords* newArray = new topWords[2*n];

    for (int i = 0; i < n; i++)
    {
        newArray[i] = inputArray[i];
    }

    return newArray;
}

int main(int argc, char *argv[])
{
    string fileName;
    string line;
    int topNumber = 10;
    int totalWords = 0;
    int numberofDoubling = 0;
    topWords* mytopWords = new topWords[100];
    int n = 100;
    int numberofWords = 0;
    string topFifty[50] = {"the","be","to","of","and","a","in","that","have","i","it","for","not","on","with","he","as","you","do","at","this","but","his","by","from","they","we","say","her","she","or","an","will","my","one","all","would","there","their","what","so","up","out","if","about","who","get","which","go","me"};
    bool inFifty;
    bool inList;
    if (argc <= 2)
    {
        cout<<"Not enough arguments."<<endl;
        fileName = "HungerGames_edit.txt";
    }
    else
    {
        fileName = argv[1];
        topNumber = atoi(argv[2]);
    }
    ifstream readFile;
    readFile.open(fileName);
    if (readFile.fail())
    {
        cout<<"Input file opening fail."<<endl;
    }
    else
    {
        while(!readFile.eof())
        {
            getline(readFile, line,' ');
            line.erase(remove_if(line.begin(), line.end(), (int(*)(int))isspace), line.end());
            if (!line.empty())
            {
                inFifty = false;
                inList = false;
                //cout<<"*"<<line<<"*"<<endl;
                for (int i = 0; i < 50; i++)
                {
                    if (line == topFifty[i])
                    {
                        inFifty = true;
                        //cout<<"in fifty"<<endl;
                        break;
                    }
                }

                if (inFifty == false)
                {
                    totalWords ++;
                    if (numberofWords == n)
                    {
                        //cout<<"doubling"<<endl;
                        numberofDoubling ++;
                        topWords* tempWords = new topWords[2*n];
                        tempWords = ArrayDynamicAllocation(mytopWords, n);
                        delete []mytopWords;
                        mytopWords = tempWords;
                        n = n * 2;
                    }

                    for (int i = 0; i < numberofWords; i++)
                    {

                        if (mytopWords[i].word == line)
                        {
                            //cout<<"count"<<endl;
                            mytopWords[i].counts ++;
                            //cout<<mytopWords[i].word<<" "<<mytopWords[i].counts<<endl;
                            inList = true;
                            break;
                        }

                    }

                    if (inList == false)
                    {
                        mytopWords[numberofWords].word = line;
                        mytopWords[numberofWords].counts = 1;
                        //cout<<"add"<<endl;
                        //cout<<mytopWords[numberofWords].word<<" "<<mytopWords[numberofWords].counts<<endl;
                        numberofWords ++;

                    }

                }

            }

        }

    }

    sort(mytopWords, mytopWords + numberofWords, sortByCounts);
    for (int i = 0; i < topNumber; i++)
    {
        cout<<mytopWords[i].counts<<" - "<<mytopWords[i].word<<endl;
    }

    cout<<"#"<<endl;
    cout<<"Array doubled: "<<numberofDoubling<<endl;
    cout<<"#"<<endl;
    cout<<"Unique non-common words: "<<numberofWords<<endl;
    cout<<"#"<<endl;
    cout<<"Total non-common words: "<<totalWords<<endl;


    readFile.close();
    return 0;
}
