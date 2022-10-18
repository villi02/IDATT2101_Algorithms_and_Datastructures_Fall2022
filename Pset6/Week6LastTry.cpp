#include <iostream>
#include <list>
#include <stack>
using namespace std;

// https://www.geeksforgeeks.org/strongly-connected-components/ was used as insporation
typedef struct edge_st
{
    struct edge_st *next_edge;
    struct node_st *to_node;
} edge;

class Graph
{
    int amount_nodes, amount_edges;
    list<int> *edges;
    void fillOrder(int v, bool visited[], stack<int> &Stack);

    void DFSUtil(int v, bool visited[]);

public:
    Graph(int amount_nods, int amount_eds);
    void addNewEdge(int v, int w);

    void printSCCs();

    Graph getTransposedGraph();
};

Graph::Graph(int amount_nods, int amount_eds)
{
    this->amount_nodes = amount_nods;
    edges = new list<int>[amount_nods];
}

void Graph::DFSUtil(int v, bool visited[])
{
    visited[v] = true;
    cout << v << " ";

    list<int>::iterator i;
    for (i = edges[v].begin(); i != edges[v].end(); ++i)
        if (!visited[*i])
            DFSUtil(*i, visited);
}

Graph Graph::getTransposedGraph()
{
    Graph g(amount_nodes, amount_edges);
    for (int v = 0; v < amount_edges; v++)
    {
        list<int>::iterator i;
        for (i = edges[v].begin(); i != edges[v].end(); ++i)
        {
            g.edges[*i].push_back(v);
        }
    }
    return g;
}

void Graph::addNewEdge(int v, int w)
{
    edges[v].push_back(w);
}

void Graph::fillOrder(int v, bool visited[], stack<int> &Stack)
{

    visited[v] = true;

    list<int>::iterator i;
    for (i = edges[v].begin(); i != edges[v].end(); ++i)
        if (!visited[*i])
            fillOrder(*i, visited, Stack);

    Stack.push(v);
}

// Used code from the text book "algoritmer og datastrukturer" by Haftig, Ljosland
// Function to read graph from file
Graph getGrapFromFile(FILE *f)
{
    int amount_nodes, amount_edges;
    fscanf(f, "%i %i\n", &amount_nodes, &amount_edges);
    Graph g(amount_nodes, amount_edges);
    for (int i = 0; i < amount_edges; i++)
    {
        int from, to;
        fscanf(f, "%i %i\n", &from, &to);
        g.addEdge(from, to);
    }
    return g;
}

void Graph::printSCCs()
{
    stack<int> Stack;

    bool *visited = new bool[amount_nodes];
    for (int i = 0; i < amount_nodes; i++)
        visited[i] = false;

    for (int i = 0; i < amount_nodes; i++)
        if (visited[i] == false)
            fillOrder(i, visited, Stack);

    Graph gr = getTransposedGraph();

    for (int i = 0; i < amount_nodes; i++)
        visited[i] = false;

    while (Stack.empty() == false)
    {
        int v = Stack.top();
        Stack.pop();

        if (visited[v] == false)
        {
            gr.DFSUtil(v, visited);
            cout << endl;
        }
    }
}

// Driver program to test above functions
int main()
{
    FILE *openfile1 = fopen("ø6g1.txt", "r");
    FILE *openfile2 = fopen("ø6g2.txt", "r");
    FILE *openfile5 = fopen("ø6g5.txt", "r");
    FILE *openfile6 = fopen("ø6g6.txt", "r");

    Graph graph1 = getGrapFromFile(openfile1);
    cout << "\nStrongly linked items for: "
         << "ø6g1.txt\n";
    graph1.printSCCs();

    Graph graph2 = getGrapFromFile(openfile2);
    cout << "\nStrongly linked items for: "
         << "ø6g2.txt\n";
    graph2.printSCCs();

    Graph graph5 = getGrapFromFile(openfile5);
    cout << "\nStrongly linked items for: "
         << "ø6g5.txt\n";
    graph5.printSCCs();

    Graph graph6 = getGrapFromFile(openfile6);
    cout << "\nStrongly linked items for: "
         << "ø6g6.txt\n";
    graph6.printSCCs();

    return 0;
}