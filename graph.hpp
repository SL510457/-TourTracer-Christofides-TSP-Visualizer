#include <stdio.h>
#include <vector>
using namespace std;

class Graph {
public:
    int V;
    vector<vector<int>> adjMatrix;

    Graph(int vertices) : V(vertices), adjMatrix(vertices, vector<int>(vertices, 0)) {}

    void addEdge(int u, int v, double weight) {
        adjMatrix[u][v] = weight;
        adjMatrix[v][u] = weight;
    }
};
