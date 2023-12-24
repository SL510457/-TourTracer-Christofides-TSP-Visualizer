import math
# import numpy as np
import matplotlib.pyplot as plt
import Christofides
import random
from datetime import datetime

num_coordinates = 15
coordinates = []

min_lat, max_lat = -90, 90
min_lon, max_lon = -180, 180
for _ in range(num_coordinates):
        lat = random.uniform(min_lat, max_lat)
        lon = random.uniform(min_lon, max_lon)
        coordinates.append((lat, lon))


# dp
start_time1 = datetime.now()

min_cost = Christofides.calculate_tsp(coordinates)

end_time1 = datetime.now()


# christofides 
start_time2 = datetime.now()

graph = Christofides.Graph(num_coordinates)

for i in range(len(coordinates)):
    for j in range(i + 1, len(coordinates)):
        distance = Christofides.CalculateDistance(*coordinates[i], *coordinates[j])
        graph.addEdge(i, j, distance)

hamiltonian_path = Christofides.ChristofidesTSP.findPath(graph)
hamiltonian_path_length = Christofides.ChristofidesTSP.calculatePathLength(graph, hamiltonian_path)

end_time2 = datetime.now()



# result
print("Hamiltonian Path:", hamiltonian_path)
print("Length of Hamiltonian Path:", hamiltonian_path_length)
print("Minimum cost of DP_TSP:", min_cost)
print("Christofides is how many times of DP: ", hamiltonian_path_length/min_cost)

runtime1 = end_time1 - start_time1
print(f"DP Runtime: {runtime1}")
runtime2 = end_time2 - start_time2
print(f"Christofides Runtime: {runtime2}")