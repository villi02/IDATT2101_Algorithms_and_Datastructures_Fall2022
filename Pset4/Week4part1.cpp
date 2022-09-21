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

// Function to get lenght of linked list
int getLength(node *Node)
{
    int size = 0;
    while (Node != NULL)
    {
        Node = Node->next;
        size++;
    }
    return size;
}

// Function to print the data present in all the nodes
void printh(node *head)
{
    node *curr = head;
    while (curr != NULL)
    {
        string value = curr->data;
        cout << value;
        curr = curr->next;
    }
}

// Function to print the data present in all the nodes, from the tail
void printt(node *tail)
{
    node *curr = tail;
    while (curr != NULL)
    {
        cout << curr->data;
        curr = curr->prev;
    }
}

// A function to add zeros to a number, to get better formatting
node *paddZeros(node *sNode, int diff)
{
    if (sNode == NULL)
        return NULL;

    node *zHead = add('0');
    diff--;
    node *temp = zHead;
    while (diff--)
    {
        temp->next = add('0');
        temp = temp->next;
    }
    temp->next = sNode;
    return zHead;
}

// Function to convert the string to Linked List.
Dlist *string_to_DLL(string text, Dlist *dlist)
{
    node *head = add(text[0]);
    node *curr = head;
    node *tail = NULL;

    for (int i = 1; i < text.size(); i++)
    {
        tail = curr;
        char value = text[i];
        curr->next = add(text[i]);
        curr = curr->next;
        curr->prev = tail;
    }

    Dlist doneList;
    doneList = (Dlist){.head = head, .tail = curr};

    dlist = &doneList;
    return dlist;
}

node *subtractionHelper(node *lNode, node *sNode, bool &borrow)
{
    if (lNode == NULL && sNode == NULL && borrow == 0)
        return NULL;
    node *previous = subtractionHelper(lNode ? lNode->next : NULL, sNode ? sNode->next : NULL, borrow);

    int dL = stoi(lNode->data);
    int dS = stoi(sNode->data);
    int sub = 0;

    // If borrowing
    if (borrow)
    {
        dL--;
        borrow = false;
    }

    // If needs to borrow
    if (dL < dS)
    {
        borrow = true;
        dL = dL + 10;
    }

    // Subtract
    sub = dL - dS;

    node *curr = add(to_string(sub)[0]);
    curr->next = previous;

    return curr;
}

Dlist *subtraction(node *tail1, node *head1, node *tail2, node *head2, Dlist *dlist)
{
    node *tempHead1 = head1;
    node *tempHead2 = head2;
    node *sNode = NULL, *lNode = NULL;

    int len1 = getLength(head1);
    int len2 = getLength(head2);

    if (len1 != len2)
    {
        lNode = len1 > len2 ? head1 : head2;
        sNode = len1 > len2 ? head2 : head1;
        sNode = paddZeros(sNode, abs(len1 - len2));
    }
    else
    {
        while (head1 && head2)
        {
            if (head1->data != head2->data)
            {
                lNode = stoi(head1->data) > stoi(head2->data) ? tempHead1 : tempHead2;
                sNode = stoi(head1->data) > stoi(head2->data) ? tempHead2 : tempHead1;
                break;
            }
            head1 = head1->next;
            head2 = head2->next;
        }
        if (lNode == NULL && sNode == NULL)
        {
            Dlist doneList;
            doneList = (Dlist){.head = add('0'), .tail = add('0')};
            dlist = &doneList;
            return dlist;
        }
    }
    bool borrow = false;
    if (lNode != tempHead1)
    {
        node *head = add('-');
        head->next = subtractionHelper(lNode, sNode, borrow);
        node *traversalHead = head;
        while (traversalHead->next)
        {
            traversalHead->next->prev = traversalHead;
            traversalHead = traversalHead->next;
        }
        Dlist doneList;
        doneList = (Dlist){.head = head, .tail = traversalHead};
        dlist = &doneList;
        return dlist;
    }
    node *headNode = subtractionHelper(lNode, sNode, borrow);
    node *traversalHead = headNode;

    while (traversalHead->next)
    {
        traversalHead->next->prev = traversalHead;
        traversalHead = traversalHead->next;
    }

    Dlist doneList;
    doneList = (Dlist){.head = headNode, .tail = traversalHead};

    dlist = &doneList;
    return dlist;
}

// Function to add two numbers represented as linked list together
Dlist *addition(node *tail1, node *tail2, Dlist *dlist)
{
    node *curr1 = tail1;
    node *curr2 = tail2;

    string value = curr1->data;
    string value2 = curr2->data;

    int sum = (stoi(curr1->data) + stoi(curr2->data));
    int carry = (sum >= 10) ? 1 : 0;
    sum = sum % 10;
    node *head = add(std::to_string(sum)[0]);
    node *temp = NULL;
    node *curr = head;
    node *tail = NULL;
    curr1 = curr1->prev;
    curr2 = curr2->prev;

    // get
    while (curr1 != NULL || curr2 != NULL)
    {
        sum = carry + (curr2 ? stoi(curr2->data) : 0) + (curr1 ? stoi(curr1->data) : 0);

        carry = (sum >= 10) ? 1 : 0;

        sum = sum % 10;

        tail = curr;
        curr->next = add(std::to_string(sum)[0]);
        curr = curr->next;
        curr->prev = tail;

        if (curr1)
            curr1 = curr1->prev;
        if (curr2)
            curr2 = curr2->prev;
    }

    if (carry > 0)
    {
        tail = curr;
        curr->next = add('1');
        curr = curr->next;
        curr->prev = tail;
    }

    Dlist doneList;
    doneList = (Dlist){.head = head, .tail = curr};

    dlist = &doneList;
    return dlist;
}

// Driver code
int main()
{
    //string testNumber = "1000000000199999999991";

    // Works with maximum 22 numbers
    string number2, number1, operation;
    // Get user input
    std::cout << "Number1: ";
    std::cin >> number1;
    std::cout << "Number2: ";
    std::cin >> number2;

    node *head1 = NULL;
    node *tail1 = NULL;
    Dlist *dlist1 = NULL;
    dlist1 = string_to_DLL(number1, dlist1);
    head1 = dlist1->head;
    tail1 = dlist1->tail;

    node *head2 = NULL;
    node *tail2 = NULL;
    Dlist *dlist2 = NULL;
    dlist2 = string_to_DLL(number2, dlist2);
    head2 = dlist2->head;
    tail2 = dlist2->tail;

    Dlist *result2 = NULL;
    node *tail22 = NULL;
    node *head22 = NULL;
    result2 = addition(tail1, tail2, result2);
    tail22 = result2->tail;
    head22 = result2->head;

    std::cout << "\nNumber 1 added to Number 2 (+): ";
    printt(tail22);

    Dlist *dlistSub = NULL;
    node *subtail = NULL;
    node *subhead = NULL;
    dlistSub = subtraction(tail1, head1, tail2, head2, dlistSub);
    subtail = dlistSub->tail;
    head22 = dlistSub->head;

    cout << "\nNumber 1 subtracted by number 2 (-): ";
    printh(head22);

    return 0;
}