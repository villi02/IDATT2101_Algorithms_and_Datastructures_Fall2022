#include <cstdio>
#include <queue>
#include <vector>
#include <iostream>

using namespace std;

#define MAX 100001
#define INF numeric_limits<int>::max()
#define pb(x) push_back(x)

typedef pair<int, int> pii;

// Code inspired by: https://www.sanfoundry.com/cpp-program-implement-dijkstras-algorithm-using-queue/
// and: https://www.javatpoint.com/cpp-dijkstra-algorithm-using-priority-queue
// and: https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-using-priority_queue-stl/

struct comp
{
    bool operator()(const pii &a, const pii &b)
    {
        return a.second > b.second;
    }
};

priority_queue<pii, vector<pii>, comp> Q;
vector<pii> G[MAX];
int D[MAX];
bool F[MAX];

class Graph
{
    vector<pii> *adj_nodes;
    int amount_nodes;
    int amount_edges;

public:
    /*
        Graph(int node_amount, int amount_edges)
        {
            this->amount_nodes = node_amount;
            this->amount_edges = amount_edges;
            this->adj_nodes = new vector<pii>[node_amount];
        }
        */
    Graph(int node_amount, int edge_amount)
    {
        this->amount_nodes = node_amount;
        this->amount_edges = edge_amount;
        adj_nodes = new vector<pii>[node_amount];
    }

    void addEdge(int from, int to, int weight);

    void addGraph(FILE *f);

    void dijkstras(int start_node);

    void printAll();
};

void Graph::printAll()
{
    for (int i = 0; i < amount_nodes; i++)
    {
        cout << "\nNode from " << i;
        for (int j = 0; j < adj_nodes[i].size(); j++)
        {
            cout << "\nto " << adj_nodes[i].at(j).first << " weight " << adj_nodes[i].at(j).second << " ";
        }
    }
}

void Graph::addEdge(int from, int to, int weight)
{
    adj_nodes[from].push_back(pii(to, weight));
}

/*
// Used code from the text book "algoritmer og datastrukturer" by Haftig, Ljosland
// Function to read graph from file
Graph::Graph(FILE *f)
{
    int node_amount, edge_amount;
    fscanf(f, "%i %i\n", &node_amount, &edge_amount);

    for (int i = 0; i < edge_amount; i++)
    {
        int from, to, weight;
        fscanf(f, "%i %i %i\n", &from, &to, &weight);
        std::cout << "\nFrom " << from << " To " << to << " weight " << weight;
        addEdge(from, to, weight);
    }
}
*/

void addAllEdges(Graph g, FILE *f, int edge_amount)
{
    for (int i = 0; i < edge_amount; i++)
    {
        int from, to, weight;
        fscanf(f, "%i %i %i\n", &from, &to, &weight);
        // cout << "\nFrom " << from << " To " << to << " weight " << weight;
        g.addEdge(from, to, weight);
    }
}

void Graph::dijkstras(int start_node)
{
    int i, u, to, weight, size_edge, nodes, edges, starting;
    priority_queue<pii, vector<pii>, greater<pii> > pq;
    bool *F = new bool[amount_nodes];
    int *dist = new int[amount_nodes];
    int *prev_node = new int[amount_nodes];

    pq.push(make_pair(start_node, 0));

    for (int i = 0; i < amount_nodes; i++)
    {
        dist[i] = INF;
    }

    dist[start_node] = 0;

    while (!pq.empty())
    {
        int u = pq.top().first;
        pq.pop();
        if (F[u])
        {
            continue;
        }
        size_edge = adj_nodes[u].size();
        for (int i = 0; i < size_edge; i++)
        {
            to = adj_nodes[u].at(i).first;
            weight = adj_nodes[u].at(i).second;
            if (!F[u] && (dist[u] + weight) < dist[to])
            {
                dist[to] = dist[u] + weight;
                prev_node[to] = u;
                pq.push(pii(to, D[to]));
            }
        }
        F[u] = 1;
    }

    cout << "\n";
    // Print the result
    for (int i = 0; i < amount_nodes; i++)
    {
        cout << "Node " << i << ", prev = " << prev_node[i] << ", min_distance = " << dist[i] << endl;
    }
}

int main(int argc, char const *argv[])
{

    FILE *openfile1 = fopen("vg1.txt", "r");
    FILE *openfile2 = fopen("vg2.txt", "r");
    FILE *openfile3 = fopen("vg3.txt", "r");
    FILE *openfile4 = fopen("vg4.txt", "r");
    FILE *openfile5 = fopen("vg5.txt", "r");
    FILE *openfileSkandi = fopen("vgSkandinavia.txt", "r");

    /*
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
    */

    cout << "\nOm distanse = 2147483647, så betyr det at den ikke blir nådd" << endl;

    // vg1
    int node_amount1, edge_amount1;
    fscanf(openfile1, "%i %i\n", &node_amount1, &edge_amount1);
    Graph g1(node_amount1, edge_amount1);

    addAllEdges(g1, openfile1, edge_amount1);

    // g1.printAll();
    cout << "\nvg1 utskrift" << endl;
    g1.dijkstras(1);

    // vg5
    int node_amount5, edge_amount5;
    fscanf(openfile5, "%i %i\n", &node_amount5, &edge_amount5);
    Graph g5(node_amount5, edge_amount5);

    addAllEdges(g5, openfile5, edge_amount5);

    // g5.printAll();

    cout << "\nvg5 utskrift" << endl;
    g5.dijkstras(1);




    int fileNr, start_point;
    // Get user input
    cout << "Which file?: ";
    cin >> fileNr;
    cout << "start node: ";
    cin >> start_point;

    int node_amount11, edge_amount11;
    int node_amount22, edge_amount22;
    int node_amount33, edge_amount33;
    int node_amount44, edge_amount44;
    int node_amount55, edge_amount55;
    int node_amount66, edge_amount66;

    // Initialze all things


    FILE *openfile11 = fopen("vg1.txt", "r");
    fscanf(openfile11, "%i %i\n", &node_amount11, &edge_amount11);
    Graph g11(node_amount11, edge_amount11);

    fscanf(openfile2, "%i %i\n", &node_amount22, &edge_amount22);
    Graph g2(node_amount22, edge_amount22);

    fscanf(openfile3, "%i %i\n", &node_amount33, &edge_amount33);
    Graph g3(node_amount33, edge_amount33);

    fscanf(openfile4, "%i %i\n", &node_amount44, &edge_amount44);
    Graph g4(node_amount44, edge_amount44);

    FILE *openfile55 = fopen("vg5.txt", "r");
    fscanf(openfile55, "%i %i\n", &node_amount55, &edge_amount55);
    Graph g55(node_amount55, edge_amount55);

    fscanf(openfileSkandi, "%i %i\n", &node_amount66, &edge_amount66);
    Graph g6(node_amount66, edge_amount66);


    switch (fileNr)
    {
        case 1:

            addAllEdges(g11, openfile1, edge_amount11);

            cout << "\nvg1 utskrift" << endl;
            g11.dijkstras(start_point);
            break;

        case 2:

            addAllEdges(g2, openfile2, edge_amount22);

            cout << "\nvg2 utskrift" << endl;
            g2.dijkstras(start_point);
            break;

        case 3:

            addAllEdges(g3, openfile3, edge_amount33);

            cout << "\nvg3 utskrift" << endl;
            g3.dijkstras(start_point);
            break;

        case 4:

            addAllEdges(g4, openfile4, edge_amount44);

            cout << "\nvg4 utskrift" << endl;
            g4.dijkstras(start_point);
            break;

        case 5:

            addAllEdges(g55, openfile55, edge_amount55);

            cout << "\nvg5 utskrift" << endl;
            g55.dijkstras(start_point);
            break;

        case 6:

            addAllEdges(g6, openfileSkandi, edge_amount66);

            cout << "\nvgskandi utskrift" << endl;
            g6.dijkstras(start_point);
            break;

        default:
            cout << "\nNoe gikk gale her, kanskje du gav inn feil input" << endl;
            break;

    }
    return 0;
}