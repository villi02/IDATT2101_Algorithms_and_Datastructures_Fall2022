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

void HashTable::addToTable(int data)
{
}

int HashTable::getHash1(int input, int size)
{
    return abs(input % size);
}

int HashTable::getHash2(int input, int size)
{

    return abs(input % (size - 1) + 1);
}

// Fill vector with 10mil random numbers
vector<int> *fillVector(vector<int> *vector, int size)
{

    for (int j = 0; j < size; j++)
    {
        vector->push_back(rand() % (int)pow(10, 8) + 1);
    }
    return vector;
}

int main()
{
    vector<int> *numbers = new vector<int>;
    int *array = new int[(int)pow(10, 7)];
    int sizeOfTable = 12334093;
    HashTable *table = new HashTable(sizeOfTable);
    cout << pow(10, 7) / (double)12334093;
    vector<int> *newVector = fillVector(numbers, pow(10, 7));

    cout << "\nSize of vector: " << table->numbers->size();

    return 0;
}