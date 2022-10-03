#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <math.h>
using namespace std;

class HashTable
{
public:
    int collisions;
    int slotsUsed;
    int primeNumberForTable;
    void addToTable(string data);
    int getHash1(int input, int size);
    string getValue(string data);
    HashTable(int size)
    {
        collisions = 0;
        primeNumberForTable = 12334093;
    }
};

int HashTable::getHash1(int input, int size)
{
    return input % size;
}

int Hashtable::getHash2(int input, int size)
{

    return input % (size - 1) + 1;
}

int main()
{

    cout << pow(10, 7) / (double)12334093;
    return 0;
}