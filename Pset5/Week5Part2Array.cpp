#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <math.h>
#include <vector>
#include <map>
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
    multimap<int, int> gquiz1;
    HashTable *table = new HashTable(sizeOfTable);
    int *newArray = fillArray(numbers, pow(10, 7));
    cout << "\nDone with random numbers";

    // newVector->insert(newVector->begin() + 69, 420);
    // cout << "\nTest number: " << newVector->at(69);

    // Get starting timepoint
    chrono::steady_clock::time_point begin1 = std::chrono::steady_clock::now();

    for (int i = 0; i < int(pow(10, 7)); i++)
    {
        table->addToTable(newArray[i]);
    }

    // Get ending timepoint
    chrono::steady_clock::time_point end1 = std::chrono::steady_clock::now();
    long duration1 = std::chrono::duration_cast<std::chrono::microseconds>(end1 - begin1).count();

    cout << "\nDuration of custom hashtable: " << duration1 << "[µs]";

    // Get starting timepoint
    chrono::steady_clock::time_point begin2 = std::chrono::steady_clock::now();

    for (int i = 0; i < int(pow(10, 7)); i++)
    {
        gquiz1.insert(pair<int, int>(i, newArray[i]));
    }

    // Get ending timepoint
    chrono::steady_clock::time_point end2 = std::chrono::steady_clock::now();
    long duration2 = std::chrono::duration_cast<std::chrono::microseconds>(end2 - begin2).count();
    cout << "\nDuration of C++ built-inn multimap: " << duration2 << "[µs]";

    cout << "\nDone with hashingtable!";
    cout << "\nCollisions: " << table->collisions;
    cout << "\nLastfaktor: " << pow(10, 7) / sizeOfTable;
    cout << "\nNB! I could not find a standard hashmap built in with C++, instead i only found a multi map as the best equivalent, didn't really have traditional put or add method, and i had to create the index myself, so the multimap is not exactly the same as a hashmap, but the closest i could find";

    return 0;
}