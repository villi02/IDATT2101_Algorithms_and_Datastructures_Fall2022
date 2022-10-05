#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <math.h>
#include <vector>
using namespace std;

class HashTable
{
public:
    vector<int> *numbers;
    int collisions;
    int slotsUsed;
    int primeNumberForTable;
    void addToTable(int data);
    int getHash1(int input, int size);
    int getHash2(int input, int size);
    string getValue(string data);
    HashTable(int size)
    {
        collisions = 0;
        primeNumberForTable = size;
        numbers = new vector<int>(size);
    }
};

int HashTable::getHash1(int input, int size)
{
    return input % size;
}

int HashTable::getHash2(int input, int size)
{

    return input % (size - 1) + 1;
}

// Fill vector with 10mil random numbers
vector<int> *fillVector(vector<int> *vector, int size)
{

    for (int j = 0; j < size; j++)
    {
        vector->insert(vector->begin()+j ,rand() % (int)pow(10, 8) + 1);
    }
    return vector;
}

void HashTable::addToTable(int data)
{

    int positionHash = getHash1(data, primeNumberForTable);
    //cout << "\ndata: " << data;
    //cout << " hash: " << positionHash;

    if (numbers->at(positionHash) == 0)
    {
        numbers->insert(numbers->begin() + positionHash, data);
        return;
    }

    else 
    {
        collisions++;
        int hashStep = getHash2(data, primeNumberForTable);
        while (true)
        {
            
            positionHash = (positionHash + hashStep) % primeNumberForTable;
            if (numbers->at(positionHash) == 0)
            {
                numbers->insert(numbers->begin() + positionHash, data);
                return;
            }
        }
    }
}

int main()
{
    vector<int> *numbers = new vector<int>;
    int sizeOfTable = 12334093;
    HashTable *table = new HashTable(sizeOfTable);
    cout << pow(10, 7) / (double)12334093;
    vector<int> *newVector = fillVector(numbers, pow(10, 7));
    cout << "\nDone with random numbers";

    cout << "\nSize of vector: " << table->numbers->size();
    //newVector->insert(newVector->begin() + 69, 420);
    //cout << "\nTest number: " << newVector->at(69);

    for (int i = 0; i < newVector->size(); i++)
    {
        table->addToTable(newVector->at(i));
        if (i % 1000 == 0)
        {
            cout << "\nAdded: " << i;
        }
    }

    return 0;
}