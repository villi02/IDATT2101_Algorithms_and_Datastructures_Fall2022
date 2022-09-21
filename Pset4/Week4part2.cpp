#include <iostream>
#include <string>
#include <string.h>
#include <queue>
#include <math.h>
using namespace std;

// Structure for a Double Linked List
struct node
{
    string data;
    node *left;
    node *right;
};

struct Dlist
{
    node *head;
    node *tail;
};

// Function to add a new node to the Linked List
node *add(string data)
{
    node *newnode = new node;
    newnode->data = data;
    newnode->left = NULL;
    newnode->right = NULL;
    return newnode;
}

node *insertion(node *root, string data)
{
    if (root == NULL)
    {
        root = add(data);
        return root;
    }

    node *newNode = add(data);
    node *traversingNode = root;

    while (true)
    {
        if (traversingNode->data.compare(newNode->data) > 0)
        {
            if (traversingNode->left == NULL)
            {
                traversingNode->left = newNode;
                break;
            }

            else
            {
                traversingNode = traversingNode->left;
            }
        }
        else
        {
            if (traversingNode->right == NULL)
            {
                traversingNode->right = newNode;
                break;
            }
            else
            {
                traversingNode = traversingNode->right;
            }
        }
    }
    return root;
}

int spaces(int level, string data)
{
    int lineLength = 200;
    int needed = lineLength / pow(2, level + 1) - data.length() / 2;
    return needed;
}

queue<node *> getLevels(int level, node *root)
{
    if (root == NULL || level == 0)
    {
        queue<node *> singleque;
        singleque.push(root);
        return singleque;
    }

    queue<node *> q;
    q.push(root);
    queue<node *> iterationQue = q;

    for (int i = 0; i < level; i++)
    {
        queue<node *> tempQue;
        while (!iterationQue.empty())
        {
            node *temp = iterationQue.front();
            iterationQue.pop();
            if (temp->left != NULL)
            {
                tempQue.push(temp->left);
            }
            if (temp->right != NULL)
            {
                tempQue.push(temp->right);
            }

            if (temp->left == NULL)
            {
                tempQue.push(add(""));
            }

            if (temp->right == NULL)
            {
                tempQue.push(add(""));
            }
        }
        iterationQue = tempQue;
    }
    return iterationQue;
}

void printSpaces(int spaces)
{
    for (int i = 0; i < spaces; i++)
    {
        cout << " ";
    }
}

void printTree(node *root)
{
    if (root == NULL)
    {
        cout << "root in null";
        return;
    }

    int level = 0;
    queue<node *> oldQueue;
    while (true)
    {

        oldQueue = getLevels(level, root);
        queue<node *> traverseQueue;
        traverseQueue = getLevels(level, root);
        while (!traverseQueue.empty())
        {
            node *temp = traverseQueue.front();
            traverseQueue.pop();
            int spacesL = spaces(level, temp->data);
            printSpaces(spacesL / 2);
            cout << temp->data;
            cout << std::string(spacesL / 2, ' ');
        }
        cout << "\n";

        queue<node *> nextQueue = getLevels(level + 1, root);
        if (level >= 4 || oldQueue == nextQueue || nextQueue.size() == 0)
        {
            break;
        }

        level++;
    }
}

int main(int argc, char **argv)
{

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // virker ikke med dette, selv om det burde gå, du må legge til ønsket elementer som lengre nede, eller bruke uendelige funksjonen lengst nede//
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /*
    node *root = NULL;
    root = add(argv[0]);
    for (int i = 1; i < argc; i++)
    {
        root = insertion(root, argv[i]);
    }
    */

    /*
        // hode bein hals arm tann hånd tå
        node *root = add("hode");
        insertion(root, "bein");
        insertion(root, "hals");
        insertion(root, "arm");
        insertion(root, "tann");
        insertion(root, "hånd");
        insertion(root, "tå");
    */

    string first_word;
    std::cout << "First word: ";
    std::cin >> first_word;

    node *root = add(first_word);
    while (true)
    {
        string word;
        std::cout << "New word: ";
        std::cin >> word;
        cout << "////////////////////////////////////////////////////////////////////////////////////////////////////\n";
        insertion(root, word);
        printTree(root);
    }

    return 0;
}