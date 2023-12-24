#include <iostream>
#include <stdio.h>
#include <cmath>
#include <algorithm>
#include <limits>
#include <iomanip>
#include <string>
#include <list>
#include <vector>
#include <stack>
#include <utility>
#include <numeric>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>
#include "DP_TSP.cpp"

using namespace std;
namespace py = pybind11;

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

class ChristofidesTSP {
public:
    static vector<int> findPath(Graph& graph) {
        int n = graph.V;

        Graph minSpanningTree = minimumSpanningTree(graph);

        vector<int> oddVertices = findOddDegreeVertices(minSpanningTree);

        Graph inducedSubgraph = createInducedSubgraph(graph, oddVertices);
        Graph minWeightMatching = minimumWeightPerfectMatching(inducedSubgraph);

        combineGraphs(minSpanningTree, minWeightMatching);

        vector<int> eulerianCircuit = findEulerianCircuit(minSpanningTree);

        vector<int> hamiltonianPath = makeHamiltonian(eulerianCircuit);

        return hamiltonianPath;
    }

 static double calculatePathLength(const Graph& graph, const vector<int>& path) {
        double length = 0.0;

        for (size_t i = 0; i < path.size() - 1; ++i) {
            int u = path[i];
            int v = path[i + 1];
            length += graph.adjMatrix[u][v];
        }

        // Add the last edge
        length += graph.adjMatrix[path.back()][path.front()];

        return length;
    }

private:
    static Graph minimumSpanningTree(Graph& graph) {
        Graph minSpanningTree(graph.V);

        vector<int> parent(graph.V, -1);
        vector<int> key(graph.V, numeric_limits<int>::max());
        vector<bool> mstSet(graph.V, false);

        key[0] = 0;

        for (int count = 0; count < graph.V - 1; ++count) {
            int u = minKey(key, mstSet);
            mstSet[u] = true;

            for (int v = 0; v < graph.V; ++v) {
                if (graph.adjMatrix[u][v] && !mstSet[v] && graph.adjMatrix[u][v] < key[v]) {
                    parent[v] = u;
                    key[v] = graph.adjMatrix[u][v];
                }
            }
        }

        for (int i = 1; i < graph.V; ++i) {
            minSpanningTree.addEdge(parent[i], i, graph.adjMatrix[parent[i]][i]);
        }

        return minSpanningTree;
    }

    static int minKey(const vector<int>& key, const vector<bool>& mstSet) {
        int min = numeric_limits<int>::max();
        int minIndex = -1;

        for (int v = 0; v < key.size(); ++v) {
            if (!mstSet[v] && key[v] < min) {
                min = key[v];
                minIndex = v;
            }
        }

        return minIndex;
    }

    static vector<int> findOddDegreeVertices(const Graph& graph) {
        vector<int> oddVertices;

        for (int i = 0; i < graph.V; ++i) {
            int degree = 0;

            for (int j = 0; j < graph.V; ++j) {
                if (graph.adjMatrix[i][j] != 0) {
                    degree++;
                }
            }

            if (degree % 2 != 0) {
                oddVertices.push_back(i);
            }
        }

        return oddVertices;
    }

    static Graph createInducedSubgraph(const Graph& graph, const vector<int>& vertices) {
        int n = vertices.size();
        Graph inducedSubgraph(n);

        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                inducedSubgraph.addEdge(i, j, graph.adjMatrix[vertices[i]][vertices[j]]);
            }
        }

        return inducedSubgraph;
    }

    static Graph minimumWeightPerfectMatching(const Graph& graph) {

        Graph minWeightMatching(graph.V);

        vector<bool> used(graph.V, false);

        for (int i = 0; i < graph.V; ++i) {
            if (!used[i]) {
                int minWeight = numeric_limits<int>::max();
                int minVertex = -1;

                for (int j = i + 1; j < graph.V; ++j) {
                    if (!used[j] && graph.adjMatrix[i][j] < minWeight) {
                        minWeight = graph.adjMatrix[i][j];
                        minVertex = j;
                    }
                }

                minWeightMatching.addEdge(i, minVertex, minWeight);
                used[i] = used[minVertex] = true;
            }
        }

        return minWeightMatching;
    }

    static void combineGraphs(Graph& minSpanningTree, const Graph& minWeightMatching) {
        for (int i = 0; i < minWeightMatching.V; ++i) {
            for (int j = 0; j < minWeightMatching.V; ++j) {
                if (minWeightMatching.adjMatrix[i][j] != 0) {
                    minSpanningTree.addEdge(i, j, minWeightMatching.adjMatrix[i][j]);
                }
            }
        }
    }

    static vector<int> findEulerianCircuit(Graph& graph) {
        int startVertex = 0;

        vector<int> circuit;
        stack<int> st;
        st.push(startVertex);

        while (!st.empty()) {
            int u = st.top();

            int v;
            for (v = 0; v < graph.V; ++v) {
                if (graph.adjMatrix[u][v] != 0) {
                    break;
                }
            }

            if (v == graph.V) {
                circuit.push_back(u);
                st.pop();
            } else {
                st.push(v);
                graph.adjMatrix[u][v] = 0;
                graph.adjMatrix[v][u] = 0;
            }
        }

        reverse(circuit.begin(), circuit.end());

        return circuit;
    }

    static vector<int> makeHamiltonian(const vector<int>& eulerianCircuit) {
        vector<int> hamiltonianPath;

        for (int vertex : eulerianCircuit) {
            if (find(hamiltonianPath.begin(), hamiltonianPath.end(), vertex) == hamiltonianPath.end()) {
                hamiltonianPath.push_back(vertex);
            }
        }

        hamiltonianPath.push_back(eulerianCircuit.front());

        return hamiltonianPath;
    }
};

PYBIND11_MODULE(Christofides, m) {
    m.doc() = "";

    py::class_<Graph>(m, "Graph")
        .def(py::init<int>())
        .def("addEdge", &Graph::addEdge);

    m.def("ToRadians", &ToRadians);
    m.def("CalculateDistance", &CalculateDistance);
    m.def("calculate_tsp", &calculateTSP, "Calculate the minimum cost of TSP");
    m.def("getHamiltonianPath", &getHamiltonianPath, "get DP HamiltonianPath");

    py::class_<ChristofidesTSP>(m, "ChristofidesTSP")
        .def_static("findPath", &ChristofidesTSP::findPath)
        .def_static("calculatePathLength", &ChristofidesTSP::calculatePathLength);
}

// int main() {
    
//     int n = 4;
//     Graph graph(n);

//     double v[n][2];
//     v[0][0] = 37.7749;
//     v[0][1] = -122.4194;
//     v[1][0] = 34.0522;
//     v[1][1] = 0;
//     v[2][0] = 0;
//     v[2][1] = 0;
//     v[3][0] = 100;
//     v[3][1] = 100;
    
//     graph.addEdge(0, 1, CalculateDistance(v[0][0], v[0][1], v[1][0], v[1][1]));
//     graph.addEdge(0, 2, CalculateDistance(v[0][0], v[0][1], v[2][0], v[2][1]));
//     graph.addEdge(0, 3, CalculateDistance(v[0][0], v[0][1], v[3][0], v[3][1]));
//     graph.addEdge(1, 2, CalculateDistance(v[1][0], v[1][1], v[2][0], v[2][1]));
//     graph.addEdge(1, 3, CalculateDistance(v[1][0], v[1][1], v[3][0], v[3][1]));
//     graph.addEdge(2, 3, CalculateDistance(v[2][0], v[2][1], v[3][0], v[3][1]));

//     vector<int> hamiltonianPath = ChristofidesTSP::findPath(graph);

//     cout << "Hamiltonian Path: ";
//     for (int vertex : hamiltonianPath) {
//         cout << vertex << " ";
//     }
//     cout << endl;

//     return 0;
// }