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
    int *numbers;
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
        numbers = new int[size];
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
int *fillArray(int *array, int size)
{

    for (int j = 0; j < size; j++)
    {
        array[j] = rand() % (int)pow(10, 10) + 1;
    }
    return array;
}

void HashTable::addToTable(int data)
{

    int positionHash = getHash1(data, primeNumberForTable);
    // cout << "\ndata: " << data;
    // cout << " hash: " << positionHash;

    if (numbers[positionHash] == 0)
    {
        numbers[positionHash] = data;
        return;
    }

    else
    {
        collisions++;
        int hashStep = getHash2(data, primeNumberForTable);
        while (true)
        {

            positionHash = (positionHash + hashStep) % primeNumberForTable;
            if (numbers[positionHash] == 0)
            {
                numbers[positionHash] = data;
                return;
            }
        }
    }
}

int main()
{
    int sizeOfTable = 12334093;
    int *numbers = new int[sizeOfTable];
    HashTable *table = new HashTable(sizeOfTable);
    cout << pow(10, 7) / (double)12334093;
    int *newArray = fillArray(numbers, pow(10, 7));
    cout << "\nDone with random numbers";

    // newVector->insert(newVector->begin() + 69, 420);
    // cout << "\nTest number: " << newVector->at(69);

    for (int i = 0; i < int(pow(10, 7)); i++)
    {
        table->addToTable(newArray[i]);
    }

    cout << "\nDone with hashingtable!";

    return 0;
}