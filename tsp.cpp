#include <stdio.h>
#include <vector>
#include <stack>
#include "graph.cpp"

class ChristofidesTSP {
public:
    static vector<int> findPath(Graph& graph) {
        int n = graph.V;

        Graph minSpanningTree = minimumSpanningTree(graph);

        // Step 2: Find vertices with odd degree in T
        vector<int> oddVertices = findOddDegreeVertices(minSpanningTree);

        // Step 3: Find minimum weight perfect matching M in the induced subgraph G' (vertices with odd degree)
        Graph inducedSubgraph = createInducedSubgraph(graph, oddVertices);
        Graph minWeightMatching = minimumWeightPerfectMatching(inducedSubgraph);

        // Step 4: Combine the minimum spanning tree and the minimum weight perfect matching
        combineGraphs(minSpanningTree, minWeightMatching);

        // Step 5: Find an Eulerian circuit in the combined graph
        vector<int> eulerianCircuit = findEulerianCircuit(minSpanningTree);

        // Step 6: Make the circuit Hamiltonian
        vector<int> hamiltonianPath = makeHamiltonian(eulerianCircuit);

        return hamiltonianPath;
    }

private:
    static Graph minimumSpanningTree(Graph& graph) {
        // Prim's algorithm for minimum spanning tree
        // (You can replace this with your preferred algorithm)
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
        // Implement your own algorithm for minimum weight perfect matching
        // Here, we use a simple greedy algorithm as an example
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
        // Hierholzer's algorithm for finding Eulerian circuit
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

        // Reverse the circuit to get the correct order
        reverse(circuit.begin(), circuit.end());

        return circuit;
    }

    static vector<int> makeHamiltonian(const vector<int>& eulerianCircuit) {
        // Remove duplicate vertices to obtain Hamiltonian path
        vector<int> hamiltonianPath;

        for (int vertex : eulerianCircuit) {
            if (find(hamiltonianPath.begin(), hamiltonianPath.end(), vertex) == hamiltonianPath.end()) {
                hamiltonianPath.push_back(vertex);
            }
        }

        // Add the starting vertex to complete the Hamiltonian cycle
        hamiltonianPath.push_back(eulerianCircuit.front());

        return hamiltonianPath;
    }
};

