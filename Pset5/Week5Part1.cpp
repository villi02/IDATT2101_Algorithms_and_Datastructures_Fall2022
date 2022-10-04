#include <iostream>
#include <fstream>
#include <string>
#define FILE_NAME "navn.txt"
#include <cstdlib>
using namespace std;

// Structure for a Singly Linked List
struct node
{
    string data;
    node *next;
};

class HashTable
{
public:
    node *entries;
    int collisions;
    int slotsUsed;
    void addToTable(string data);
    int getHash(string input, int size);
    string getValue(string data);
    HashTable(int size)
    {
        entries = new node[size];
        collisions = 0;
        slotsUsed = 0;
    }
};

class LinkedList
{
public:
    node *add(node *head, string data);
};

node *add(string data)
{
    node *newnode = new node;
    newnode->data = data;
    newnode->next = NULL;
    return newnode;
};

// Function to get the hash of the input, int size is the size of the table
int HashTable::getHash(string input, int size)
{

    int hash = 0;
    for (int i = 0; i < input.size(); i++)
    {
        hash += abs(int(input[i]) * (i + 1));
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

// Function to get all the names from the text file, returns as a string array (pointer)
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

void HashTable::addToTable(string data)
{

    int hash = getHash(data, 127);
    if (entries[hash].data == "")
    {
        entries[hash].data = data;
        entries[hash].next = NULL;
        slotsUsed++;
    }
    else
    {
        cout << "\n"
             << data << " crashed with: " << entries[hash].data;
        collisions++;
        node *newnode = add(entries[hash].data);
        newnode->next = entries[hash].next;
        entries[hash].data = data;
        entries[hash].next = newnode;
    }
}
string HashTable::getValue(string data)
{
    int hash = getHash(data, 127);

    if (entries[hash].data == "")
    {
        return "\nCould not find anyone with the name: " + data;
    }
    else
    {
        if (entries[hash].data == data)
        {
            return "\nfound " + entries[hash].data;
        }

        string returnValue = "\n" + data + " crashed with " + entries[hash].data;

        node *curr = entries[hash].next;
        while (curr != NULL)
        {
            if (curr->data == data)
            {
                return returnValue + "\nFound " + curr->data;
            }
            curr = curr->next;
        }
    }
    return "\nCould not find anyone with the name: " + data;
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

    // Adding names to hashtable
    for (int i = 0; i < sizeOfArray; i++)
    {
        table->addToTable(names[i]);
    }

    cout << "\n\nShould be my name: " << table->entries[table->getHash("Vilhjalmur Arnar Vilhjalmsson", 127)].data;
    cout << "\nShould also be my name: " << table->getValue("Vilhjalmur Arnar Vilhjalmsson");

    cout << "\n\nPrinting everyone who crashed with Aleksander Halvorsen Holthe: ";
    node *curr = table->entries[table->getHash("Aleksander Halvorsen Holthe", 127)].next;
    while (curr != NULL)
    {
        cout << "\nCrashed also: " << curr->data;
        curr = curr->next;
    }

    // Collisions
    cout << "\n\nAmount of collisions: " << table->collisions;
    double colPrPers = table->collisions / (double)sizeOfArray;
    cout << "\nCollision pr person: " << colPrPers;

    // Slots used in table
    cout << "\n\nAmounts of slots used in table: " << table->slotsUsed;
    cout << "\nElementer i tabell: " << 114;
    cout << "\nStørrelse på tabell: " << 127;
    cout << "\nLastfaktor: " << 114 / (double)127;

    // Enable user to test the lookup
    string lookupName;
    while (lookupName != "stopp")
    {
        // Get user input
        cout << "\nName to look up: ";
        getline(cin, lookupName);
        cout << table->getValue(lookupName);
    }

    return 0;
}