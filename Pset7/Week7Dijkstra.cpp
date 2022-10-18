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
    bool visited;
    void *d;
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
        G->nodes[i].visited = false;
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