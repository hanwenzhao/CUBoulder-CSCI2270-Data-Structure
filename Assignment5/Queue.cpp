#include "Queue.h"

using namespace std;

Queue::Queue(int qs)
{
    //ctor
    queueSize = qs;
    arrayQueue = new string[queueSize];
    queueCount = 0;
    queueHead = 0;
    queueTail = 0;
}

Queue::~Queue()
{
    //dtor
}

void Queue::enqueue(string word)
{
    if (!queueIsFull())
    {
        arrayQueue[queueTail] = word;
        queueCount ++;
        if (queueTail == queueSize-1)
        {
            //cout << "set tail to 0" << endl;
            queueTail = 0;
        }
        else
        {
            queueTail ++;
        }
        cout<<"E: "<<word<<endl;
        cout<<"H: "<<queueHead<<endl;
        cout<<"T: "<<queueTail<<endl;
    }
    else
    {
        cout << "Queue is full." << endl;
    }
}

string Queue::dequeue()
{
    string word;
    if (!queueIsEmpty())
    {
        word = arrayQueue[queueHead];
        queueCount --;
        if (queueHead == queueSize - 1)
        {
            queueHead = 0;
        }
        else
        {
            queueHead ++;
        }
        cout<<"H: "<<queueHead<<endl;
        cout<<"T: "<<queueTail<<endl;
        cout<<"word: "<<word<<endl;
    }
    else
    {
        cout << "Queue is empty." << endl;
    }

    return word;
}

void Queue::printQueue()
{
    if (!queueIsEmpty())
    {
        for (int i = 0; i < queueCount; i++)
        {
            int x = queueHead + i;
            if (x >= 10)
            {
                x = x - 10;
            }
            cout << x << ": " << arrayQueue[x] << endl;
        }
    }
    else
    {
        cout << "Empty" << endl;
    }

}

bool Queue::queueIsFull()
{
    if (queueCount == queueSize)
    {
        return true;
    }
    else
    {
        return false;
    }

}

bool Queue::queueIsEmpty()
{
    if (queueCount == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
