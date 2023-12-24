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
#include "DP_TSP.hpp"

using namespace std;
namespace py = pybind11;

const int MAX = 1000000;

int n;
int dist[100][100];
int memo[100][1 << 12];
std::vector<int> path[100][1 << 12];  // Record path during DP

int fun(int i, int mask) {
    if (mask == ((1 << i) | 1))
        return dist[0][i];

    if (memo[i][mask] != 0)
        return memo[i][mask];

    int res = MAX;
    int best_j = -1;

    for (int j = 1; j < n; ++j) {
        if ((mask & (1 << j)) && j != i) {
            int current_res = fun(j, mask & (~(1 << i))) + dist[j][i];
            if (current_res < res) {
                res = current_res;
                best_j = j;
            }
        }
    }

    memo[i][mask] = res;
    path[i][mask] = path[best_j][mask & (~(1 << i))];  // Update path
    path[i][mask].push_back(i);  // Add current node to path

    return res;
}

std::vector<int> getHamiltonianPath(const std::vector<std::pair<double, double>>& coordinates) {
    n = coordinates.size();

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            double x1 = coordinates[i].first;
            double y1 = coordinates[i].second;
            double x2 = coordinates[j].first;
            double y2 = coordinates[j].second;
            dist[i][j] = CalculateDistance(x1, y1, x2, y2);
        }
    }

    int ans = MAX;
    int start = -1;

    for (int i = 1; i < n; ++i) {
        int current_ans = fun(i, (1 << n) - 1) + dist[i][0];
        if (current_ans < ans) {
            ans = current_ans;
            start = i;
        }
    }

    std::vector<int> hamiltonianPath = path[start][(1 << n) - 1];
    hamiltonianPath.push_back(start);
    std::reverse(hamiltonianPath.begin(), hamiltonianPath.end());

    return hamiltonianPath;
}

int calculateTSP(const std::vector<std::pair<double, double>>& coordinates) {
    n = coordinates.size();

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            double x1 = coordinates[i].first;
            double y1 = coordinates[i].second;
            double x2 = coordinates[j].first;
            double y2 = coordinates[j].second;
            dist[i][j] = CalculateDistance(x1, y1, x2, y2);
        }
    }

    int ans = MAX;

    for (int i = 1; i < n; ++i) {
        ans = std::min(ans, fun(i, (1 << n) - 1) + dist[i][0]);
    }

    return ans;
}