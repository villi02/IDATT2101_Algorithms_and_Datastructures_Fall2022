#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <stdio.h>
#define INF 99999999;
using namespace std;

// Used code from the text book "algoritmer og datastrukturer" by Haftig, Ljosland
// Struct for node
typedef struct node_st
{
    int number;
    struct edge_st *start_edge;
    void *d;
} node;

// Used code from the text book "algoritmer og datastrukturer" by Haftig, Ljosland
// Struct for an edge
typedef struct edge_st
{
    struct edge_st *next_edge;
    struct node_st *to_node;
    int weight;
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
/////////////////////////////////////////////////////
//////////////////  Not finished  ///////////////////
/////////////////////////////////////////////////////
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
        int from, to, weight;
        edge *e = (edge *)malloc(sizeof(edge));
        fscanf(f, "%i %i %i\n", &from, &to, &e->weight);
        e->to_node = &G->nodes[to];
        e->to_node->number = to;
        e->next_edge = G->nodes[from].start_edge;
        G->nodes[from].start_edge = e;
    }
    return G;
}

int main(int argc, char const *argv[])
{

    FILE *openfile1 = fopen("vg1.txt", "r");
    FILE *openfile2 = fopen("vg2.txt", "r");
    FILE *openfile3 = fopen("vg3.txt", "r");
    FILE *openfile4 = fopen("vg4.txt", "r");
    FILE *openfile5 = fopen("vg5.txt", "r");
    FILE *openfileSkandi = fopen("vgSkandinavia.txt", "r");

    Graph *g = getNewGraph(openfile1);

    for (int i = 0; i < g->amount_nodes; i++)
    {
        edge *nextEdge = g->nodes[i].start_edge;
        while (nextEdge != NULL)
        {
            cout << "\nFrom " << i << " to " << nextEdge->to_node->number << " weight " << nextEdge->weight;
            nextEdge = nextEdge->next_edge;
        }
    }


    return 0;
}
