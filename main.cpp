#include <iostream>
#include <cmath>
#include <algorithm>
#include <limits>
#include <iomanip>
#include <string>
#include <list>
#include "tsp.cpp"

using namespace std;




static double ToRadians(double degrees) {
            return degrees * M_PI / 180.0;
        }

static double CalculateDistance(double lat1, double lon1, double lat2, double lon2) {
            double lat1Rad = ToRadians(lat1);
            double lon1Rad = ToRadians(lon1);
            double lat2Rad = ToRadians(lat2);
            double lon2Rad = ToRadians(lon2);
     
            const double earthRadius = 6371.0;
     
            double deltaLat = lat2Rad - lat1Rad;
            double deltaLon = lon2Rad - lon1Rad;
     
            double a = sin(deltaLat / 2) * sin(deltaLat / 2) +
                       cos(lat1Rad) * cos(lat2Rad) *
                       sin(deltaLon / 2) * sin(deltaLon / 2);
            double c = 2 * atan2(sqrt(a), sqrt(1 - a));
            double distance = earthRadius * c;
     
            return distance;
        }


int main() {
    
    int n;
    cin >> n;
    Graph graph(n);
    
    

    double v[n][2];
    v[0][0] = 37.7749;
    v[0][1] = -122.4194;
    v[1][0] = 34.0522;
    v[1][1] = -118.2437;
    v[2][0] = 0;
    v[2][1] = 0;
    v[3][0] = 100;
    v[3][1] = 100;
    
    graph.addEdge(0, 1, CalculateDistance(v[0][0], v[0][1], v[1][0], v[1][1]));
    graph.addEdge(0, 2, CalculateDistance(v[0][0], v[0][1], v[2][0], v[2][1]));
    graph.addEdge(0, 3, CalculateDistance(v[0][0], v[0][1], v[3][0], v[3][1]));
    graph.addEdge(1, 2, CalculateDistance(v[1][0], v[1][1], v[2][0], v[2][1]));
    graph.addEdge(1, 3, CalculateDistance(v[1][0], v[1][1], v[3][0], v[3][1]));
    graph.addEdge(2, 3, CalculateDistance(v[2][0], v[2][1], v[3][0], v[3][1]));

    vector<int> hamiltonianPath = ChristofidesTSP::findPath(graph);

    cout << "Hamiltonian Path: ";
    for (int vertex : hamiltonianPath) {
        cout << vertex << " ";
    }
    cout << endl;

    return 0;
}
