#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <stdio.h>
#include <vector>
#include <map>
#include <iterator>
#include <queue>
#define INF std::numeric_limits<int>::max();
using namespace std;

// Defining Huffman Tree Node
struct Node
{
    char data;
    unsigned freq;
    string code;
    Node *left, *right;

    Node()
    {
        left = right = NULL;
    }
};

// Used from previous practice set
struct comp
{
    bool operator()(Node *a, Node *b)
    {
        return a->freq > b->freq;
    }
};

// Class to define Huffman values and methods
class Huffman
{
private:
    vector<Node *> asciiVal;

    fstream inFile, outFile;

    string inFileName, outFileName;

    priority_queue<Node *, vector<Node *>, comp> heap;

public:
    // Constructor
    Huffman(string inFileName, string outFileName)
    {
        this->inFileName = inFileName;
        this->outFileName = outFileName;

        // Will be used as frequency table
        for (int i = 0; i < 128; i++)
        {
            asciiVal.push_back(new Node());
            asciiVal[i]->data = i;
            asciiVal[i]->freq = 0;
        }
        readUncompressedBytes();
    }

    Node *root;

    // Creates a huffman tree (to get the binary codes later on)
    void createHuffTree();

    // decimalToBinary converts a decimal number to binary number
    void decimalToBinary();

    // binaryToDecimal converts a binary number to decimal
    int binaryToDecimal(char *str);

    // createCodes creates the codes (as a string) based on the huffman tree
    void createCodes(Node *root, string str);

    // readUncompromissedBytes reads infile and initializes huffmann to get ready for functions
    void readUncompressedBytes();

    // Compressing input file
    void compressFile();
    // Decrompressing input file
    void decompressFile();
};

int Huffman::binaryToDecimal(char *str)
{
    int val = 0;

    while (*str != '\0')
        val = 2 * val + (*str++ - '0');

    return val;
}

void Huffman::readUncompressedBytes()
{
    // open file
    inFile.open(inFileName, ios::in);
    char *buffer;

    // get length of file
    inFile.seekg(0, inFile.end);
    size_t length = inFile.tellg();
    inFile.seekg(0, inFile.beg);
    buffer = (char *)malloc(length * sizeof(char));
    inFile.close();

    // Create frequency table
    inFile.open(inFileName, ios::in);
    char byte;
    inFile.get(byte);
    while (!inFile.eof())
    {
        asciiVal[byte]->freq++;
        inFile.get(byte);
    }

    // Add to min heap (priority queue)
    for (int i = 0; i < 128; i++)
    {
        if (asciiVal[i]->freq != 0)
        {
            heap.push(asciiVal[i]);
        }
    }
}

void Huffman::createHuffTree()
{
    Node *right_node, *left_node;
    priority_queue<Node *, vector<Node *>, comp> tempQueue(heap);

    while (tempQueue.size() != 1)
    {
        left_node = tempQueue.top();
        tempQueue.pop();

        right_node = tempQueue.top();
        tempQueue.pop();

        root = new Node();
        root->left = left_node;
        root->right = right_node;
        int rootvalue = left_node->freq + right_node->freq;
        root->freq = left_node->freq + right_node->freq;

        tempQueue.push(root);
    }
}

void Huffman::createCodes(Node *node, string str)
{
    if (node->left == NULL && node->right == NULL)
    {
        node->code = str;
        printf("code for %c: %s \n", node->data, node->code.c_str());
        return;
    }

    createCodes(node->left, str + '0');
    createCodes(node->right, str + '1');
}

void Huffman::compressFile()
{
    // initialize components
    inFile.open(inFileName, ios::in);
    string binaryString = "";
    char asci;
    string inputString = "";

    // Metadata is structured like: size_of_heap->(for each char in heap) char -> frequency
    inputString += (char)heap.size();
    priority_queue<Node *, vector<Node *>, comp> tempQueue(heap);
    Node *topNode;

    while (tempQueue.size() > 0)
    {
        topNode = tempQueue.top();
        tempQueue.pop();
        inputString += (char)topNode->data;
        inputString += (char)topNode->freq;
        cout << topNode->data << " " << topNode->freq << endl;
    }

    // Iterate through each character in inputfile to translate to make binary string
    inFile.get(asci);
    while (!inFile.eof())
    {
        binaryString += asciiVal[asci]->code;
        // Can't write on a bit by bit basis, thus need to fill a byte and write the value of that directly
        while (binaryString.length() > 8)
        {
            //inputString += (char)binaryToDecimal((char*)binaryString.substr(0, 8));
            binaryString = binaryString.substr(8);
        }

        inFile.get(asci);
    }

    // the huffman endoded bytes will not always be a multiple of 8, thus we need to deal with the leftover bytes, and keep track as to not include them in the decompression
    int bitsLeft = 8 - binaryString.length();
    if (bitsLeft > 0)
    {
        for (int i = 0; i < bitsLeft; i++)
        {
            binaryString += '0';
        }
        //inputString += (char)binaryToDecimal(binaryString.substr(0, 8));
        // The last byte of the decompressed file will be the amount of padded zeros to ignore, so read the bits until the bitsleft-th bit
        inputString += (char)bitsLeft;
    }

    // outfile.write)
    // inFile.close();
}

// code to read bytes from file is gotten from here: https://stackoverflow.com/questions/36658734/c-get-all-bytes-of-a-file-in-to-a-char-array
int *readFileBytesUncompressed(string fileName)
{
    // open file
    ifstream infile(fileName);
    char *buffer;

    // get length of file
    infile.seekg(0, infile.end);
    size_t length = infile.tellg();
    infile.seekg(0, infile.beg);
    buffer = (char *)malloc(length * sizeof(char));

    cout << "\nlength: " << length << endl;

    // read file
    if (length > 0)
    {
        infile.read(buffer, length);
    }

    for (int i = 0; i < length; i++)
    {
        cout << "\n"
             << buffer[i];
    }

    /*
    int chars_read = infile.gcount();
    cout << "\nAmount of characters read: " << chars_read << endl;
    cout << "\nBuffer:" << endl;
    for (int i = 0; i < chars_read; i++)
    {
        cout << "\n"
             << buffer[i];
    }

    ifstream newinfile(fileName);
    while (!newinfile.eof())
    {
        printf("\n");
        printf("%02X ", newinfile.get());
    }
    */

    // create frequency table
    int frequency_table[256];
    for (int i = 0; i < 256; i++)
    {
        frequency_table[i] = 0;
    }

    ifstream newinfile(fileName);
    char byte;
    newinfile.get(byte);
    while (!newinfile.eof())
    {
        frequency_table[byte]++;
        newinfile.get(byte);
    }

    cout << "\nFrequency of a: " << frequency_table[97];

    // Write to output file
    ofstream myFile("ggtestt.txt", ios::out | ios::binary);
    myFile.write(buffer, length);

    return 0;
}

// Got the way to implement this from here: https://stackoverflow.com/questions/1856514/writing-files-in-bit-form-to-a-file-in-c?rq=1
int writeBit(int bit)
{

    return 0;
}

int main()
{
    string fileName1 = "testfile.txt";
    string treetest = "testTreefile.txt";
    string fileName2 = "testfileaa.txt";
    string fileNameOut = "outputfile.txt";
    // int *gg = readFileBytesUncompressed(fileName2);

    Huffman h(treetest, fileNameOut);

    h.createHuffTree();
    h.createCodes(h.root, "");
    h.compressFile();
}