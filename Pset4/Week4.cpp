#include <iostream>
#include <string>
using namespace std;

// Structure for a Double Linked List
struct node
{
    string data;
    node *next;
    node *prev;
};

struct Dlist
{
    node *head;
    node *tail;
};

// Function to add a new node to the Linked List
node *add(char data)
{
    node *newnode = new node;
    newnode->data = data;
    newnode->next = NULL;
    newnode->prev = NULL;
    return newnode;
}

// Function to convert the string to Linked List.
Dlist *string_to_DLL(string text, Dlist *dlist)
{
    node *head = add(text[0]);
    node *curr = head;

    node *tail = NULL;

    // curr pointer points to the current node
    // where the insertion should take place
    for (int i = 1; i < text.size(); i++)
    {
        tail = curr;
        curr->next = add(text[i]);
        curr = curr->next;
        curr->prev = tail;
    }
    Dlist doneList;
    doneList = (Dlist){.head = head, .tail = curr};

    dlist = &doneList;
    return dlist;
}

// Function to print the data present in all the nodes
void printh(node *head)
{
    node *curr = head;
    while (curr != NULL)
    {
        cout << curr->data << "->";
        curr = curr->next;
    }
}

// Function to print the data present in all the nodes, from the tail
void printt(node *tail)
{
    node *curr = tail;
    while (curr != NULL)
    {
        cout << curr->data << "->";
        curr = curr->prev;
    }
}

// Function to add two numbers represented as linked list together
Dlist *addition(node *tail1, node *tail2)
{
    node *curr1 = tail1;
    node *curr2 = tail2;
    node *head = add();
    node *curr = head;
    int carry = 0, sum;

    while (curr1 != NULL && curr2 != NULL)
    {
        int sum = carry + (curr2 ? stoi(curr2->data) : 0) + (curr1 ? stoi(curr1->data) : 0);

        carry = (sum >= 10) ? 1 : 0;

        sum = sum % 10;

        temp = add(std::to_string(sum));

        curr1 = curr1->next;
        curr2 = curr2->next;
    }
}

// Driver code
int main()
{

    string number2, number1, operation;

    /*
        // Get user input
        std::cout << "Number1: ";
        std::cin >> number1;
        std::cout << "Number2: ";
        std::cin >> number2;

        std::cout << "Operation(+ or -): ";
        std::cin >> operation;
    */

    number1 = "111111";
    number2 = "222222";

    node *head1 = NULL;
    node *tail1 = NULL;
    Dlist *dlist1 = NULL;
    dlist1 = string_to_DLL(number1, dlist1);
    head1 = dlist1->head;
    tail1 = dlist1->tail;

    /*
        node *head2 = NULL;
        node tail2;
        head2 = string_to_DLL(number2, head2, &tail2);
    */

    std::cout << "Tail1: " << tail1->data << "\n";
    std::cout << "Tail2 2nd element: " << tail1->prev->data << "\n";

    std::cout << "Print with head ";
    printh(head1);
    std::cout << "\n";
    std::cout << "Print with tail ";
    printt(tail1);
    return 0;
}