import math
import numpy as np
import matplotlib.pyplot as plt
import DP

num_coordinates = int(input("Enter the number of coordinates: "))

coordinates = []
for i in range(num_coordinates):
    lat = float(input(f"Enter latitude for coordinate {i + 1}: "))
    lon = float(input(f"Enter longitude for coordinate {i + 1}: "))
    coordinates.append((lat, lon))

min_cost = DP.calculate_tsp(coordinates)

print("Minimum cost of TSP:", min_cost)