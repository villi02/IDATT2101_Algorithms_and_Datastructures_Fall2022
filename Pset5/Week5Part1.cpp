#include <iostream>
#include <fstream>
#include <string>
#define FILE_NAME "navn.txt"
using namespace std;

// Structure for a Double Linked List
struct node
{
    string data;
    string value;
    node *next;
};

class HashTable
{
public:
    string *entries;
    void addToTable();
    double getLastFactor();
    int getHash(string input);
    HashTable(int size) {
        entries = new string[size];
    }

};

class LinkedList
{
public:
    node *add(node *head, string data);
};

node *LinkedList::add(node *head, string data)
{
    node *newnode = new node;
    newnode->data = data;
    newnode->next = head;
    head = newnode;
    return newnode;
};

int HashTable::getHash(string input, int size)
{

    int hash = 0;
    for (int i = 1; i < input.size(); i++)
    {
        hash += int(input[i]) * i;
    }

    return hash % size;
}

int getLines()
{
    unsigned int number_of_lines = 0;
    FILE *infile = fopen(FILE_NAME, "r");
    int ch;

    while (EOF != (ch = getc(infile)))
        if ('\n' == ch)
            ++number_of_lines;
    fclose(infile);
    return number_of_lines;
}

string *getNames()
{

    int number_of_names = getLines();
    string *names = new string[number_of_names];

    ifstream file(FILE_NAME);
    string str;
    int name_nr = 0;
    while (getline(file, str))
    {
        names[name_nr] = str;
        name_nr++;
    }
    return names;
}

int main()
{
    // Initalize an array of string, with the size of the next prime number (127) as the number of names is 114
    int sizeOfTable = 127;
    HashTable *table = new HashTable(sizeOfTable);
    string *names = getNames();
    int sizeOfArray = 0;
    while (!names[sizeOfArray].empty())
        ++sizeOfArray;

    for (int i = 0; i < sizeOfArray; i++)
    {
        cout << names[i] << "\n";
    }

    cout << "names size: " << table->getHash();

    return 0;
}