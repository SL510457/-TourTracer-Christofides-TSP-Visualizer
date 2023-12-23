import math
import numpy as np
import matplotlib.pyplot as plt
import Christofide

num_coordinates = int(input("Enter the number of coordinates: "))

graph = Christofide.Graph(num_coordinates)

coordinates = []
for i in range(num_coordinates):
    lat = float(input(f"Enter latitude for coordinate {i + 1}: "))
    lon = float(input(f"Enter longitude for coordinate {i + 1}: "))
    coordinates.append((lat, lon))

for i in range(len(coordinates)):
    for j in range(i + 1, len(coordinates)):
        distance = Christofide.CalculateDistance(*coordinates[i], *coordinates[j])
        graph.addEdge(i, j, distance)

hamiltonian_path = Christofide.ChristofidesTSP.findPath(graph)
hamiltonian_path_length = Christofide.ChristofidesTSP.calculatePathLength(graph, hamiltonian_path)

print("Hamiltonian Path:", hamiltonian_path)
print("Length of Hamiltonian Path:", hamiltonian_path_length)