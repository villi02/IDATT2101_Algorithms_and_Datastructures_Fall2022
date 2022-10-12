#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <stdio.h>
using namespace std;

// Used code from the text book "algoritmer og datastrukturer" by Haftig, Ljosland
// Struct for node
typedef struct node_st
{
    int number;
    struct edge_st *start_edge;
} node;

// Used code from the text book "algoritmer og datastrukturer" by Haftig, Ljosland
// Struct for an edge
typedef struct edge_st
{
    struct edge_st *next_edge;
    struct node_st *to_node;
} edge;

// Used code from the text book "algoritmer og datastrukturer" by Haftig, Ljosland
// Struct for a graph
typedef struct
{
    int amount_nodes, amount_edges;
    node *nodes;
} Graph;

// Used code from the text book "algoritmer og datastrukturer" by Haftig, Ljosland
// Function to read graph from file
Graph *getNewGraph(FILE *f)
{
    Graph *G = (Graph *)malloc(sizeof(Graph));
    fscanf(f, "%i %i\n", &G->amount_nodes, &G->amount_edges);
    G->nodes = (node *)calloc(G->amount_nodes, sizeof(node));
    for (int i = 0; i < G->amount_nodes; i++)
    {
        G->nodes[i].number = i;
    }
    for (int i = 0; i < G->amount_edges; i++)
    {
        int from, to;
        edge *e = (edge *)malloc(sizeof(edge));
        fscanf(f, "%i %i\n", &from, &to);
        e->to_node = &G->nodes[to];
        e->to_node->number = to;
        e->next_edge = G->nodes[from].start_edge;
        G->nodes[from].start_edge = e;
    }
    return G;
}

Graph *getTransposedGraph(Graph *g)
{
    Graph *newGraph = (Graph *)malloc(sizeof(Graph));
    newGraph->nodes = (node *)calloc(g->amount_nodes, sizeof(node));
    newGraph->amount_nodes = g->amount_nodes;
    newGraph->amount_edges = g->amount_edges;
    for (int i = 0; i < newGraph->amount_nodes; i++)
    {
        newGraph->nodes[i].number = i;
    }

    for (int i = 0; i < newGraph->amount_nodes; i++)
    {
        edge *nextEdge = g->nodes[i].start_edge;
        while (nextEdge != NULL)
        {
            edge *newEdge = (edge *)malloc(sizeof(edge));
            int to = i;
            int from = nextEdge->to_node->number;
            newEdge->to_node = &newGraph->nodes[to];
            newEdge->to_node->number = to;
            newEdge->next_edge = newGraph->nodes[from].start_edge;
            newGraph->nodes[from].start_edge = newEdge;
            nextEdge = nextEdge->next_edge;
        }
    }
    return newGraph;
}

// Function to return the amount of entries in the file
int getLines(string fileName)
{
    const char *fileName_char = fileName.c_str();
    unsigned int number_of_lines = 0;
    FILE *infile = fopen(fileName_char, "r");
    int ch;

    while (EOF != (ch = getc(infile)))
        if ('\n' == ch)
            ++number_of_lines;
    fclose(infile);
    return number_of_lines;
}

int main()
{
    FILE *openfile = fopen("o6g1.txt", "r");
    // cout << getLines("o6g1.txt");
    // getGraph("o6g1.txt");
    Graph *g = getNewGraph(openfile);

    cout << "\nOriginal graph: ";
    // How to iterate through all node connections
    for (int i = 0; i < g->amount_nodes; i++)
    {
        edge *nextEdge = g->nodes[i].start_edge;
        while (nextEdge != NULL)
        {
            cout << "\n " << i << " " << nextEdge->to_node->number;
            nextEdge = nextEdge->next_edge;
        }
    }

    cout << "\nNew graph: ";
    Graph *newGraph = getTransposedGraph(g);
    // How to iterate through all node connections
    for (int i = 0; i < newGraph->amount_nodes; i++)
    {
        edge *nextEdge = newGraph->nodes[i].start_edge;
        while (nextEdge != NULL)
        {
            cout << "\n " << i << " " << nextEdge->to_node->number;
            nextEdge = nextEdge->next_edge;
        }
    }
}