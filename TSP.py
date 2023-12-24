import math
import matplotlib.pyplot as plt
import Christofides
import random
from datetime import datetime
import os

num_coordinates = 5
coordinates = []

min_lat, max_lat = -90, 90
min_lon, max_lon = -180, 180
for _ in range(num_coordinates):
    lat = random.uniform(min_lat, max_lat)
    lon = random.uniform(min_lon, max_lon)
    coordinates.append((lat, lon))

graph = Christofides.Graph(num_coordinates)
for i in range(len(coordinates)):
    for j in range(i + 1, len(coordinates)):
        distance = Christofides.CalculateDistance(*coordinates[i], *coordinates[j])
        graph.addEdge(i, j, distance)

# dp
start_time1 = datetime.now()
dp_hamiltonian_path = Christofides.getHamiltonianPath(coordinates)
dp_min_cost = Christofides.calculate_tsp(coordinates)
end_time1 = datetime.now()

# christofides 
start_time2 = datetime.now()
hamiltonian_path = Christofides.ChristofidesTSP.findPath(graph)
hamiltonian_path_length = Christofides.ChristofidesTSP.calculatePathLength(graph, hamiltonian_path)
end_time2 = datetime.now()

# result
print("Christofides' Hamiltonian Path:", hamiltonian_path)
print("Length of Hamiltonian Path:", hamiltonian_path_length)
print("DP's Hamiltonian Path:", dp_hamiltonian_path)
print("Length of DP_TSP:", dp_min_cost)
print("Christofides is how many times of DP: ", hamiltonian_path_length/dp_min_cost)

runtime1 = end_time1 - start_time1
print(f"DP Runtime: {runtime1}")
runtime2 = end_time2 - start_time2
print(f"Christofides Runtime: {runtime2}")

with open('performance.txt', 'w') as file:
    file.write(f"Christofides' Hamiltonian Path: {hamiltonian_path}\n")
    file.write(f"Length of Hamiltonian Path: {hamiltonian_path_length}\n")
    file.write(f"DP's Hamiltonian Path: {dp_hamiltonian_path}\n")
    file.write(f"Length of DP_TSP: {dp_min_cost}\n")
    file.write(f"Christofides is how many times of DP: {hamiltonian_path_length / dp_min_cost}\n")
    file.write(f"DP Runtime: {runtime1}\n")
    file.write(f"Christofides Runtime: {runtime2}\n")

print("Performance metrics written to performance.txt.")


# # Plot coordinates
# plt.figure(figsize=(6, 6))
# plt.scatter(*zip(*coordinates), c='blue', label='Coordinates')

# # Annotate each point with latitude, longitude, and node number
# for i, (lat, lon) in enumerate(coordinates):
#     plt.annotate(f'Node {i}\nLat: {lat:.2f}\nLon: {lon:.2f}', (lat, lon),
#                  textcoords="offset points", xytext=(0, 5), ha='center', fontsize=8, color='black')

# # Plot Hamiltonian path from Christofides algorithm
# hamiltonian_path_coordinates = [coordinates[i] for i in hamiltonian_path]
# hamiltonian_path_coordinates.append(hamiltonian_path_coordinates[0])  # Connect back to the starting point
# hamiltonian_path_x, hamiltonian_path_y = zip(*hamiltonian_path_coordinates)
# plt.plot(hamiltonian_path_x, hamiltonian_path_y, c='red', linestyle='-', linewidth=2, label='Christofides Path')

# # Plot Hamiltonian path from dynamic programming solution
# dp_hamiltonian_path_coordinates = [coordinates[i] for i in dp_hamiltonian_path]
# dp_hamiltonian_path_coordinates.append(dp_hamiltonian_path_coordinates[0])  # Connect back to the starting point
# dp_hamiltonian_path_x, dp_hamiltonian_path_y = zip(*dp_hamiltonian_path_coordinates)
# plt.plot(dp_hamiltonian_path_x, dp_hamiltonian_path_y, c='green', linestyle='-', linewidth=2, label='DP Path')

# # Annotate Hamiltonian path length
# hamiltonian_path_length_str = f'Christofides Length: {hamiltonian_path_length:.2f}\nDP Length: {dp_min_cost:.2f}'
# plt.annotate(hamiltonian_path_length_str, xy=(0.5, 0.95), xycoords='axes fraction', ha='center', fontsize=12, color='black')

# # Set labels and legend
# plt.title('Traveling Salesman Problem - Christofides vs DP')
# plt.legend()

# # Hide axis labels and ticks
# plt.xticks([])
# plt.yticks([])

# # Create the 'result' folder if it doesn't exist
# os.makedirs('result', exist_ok=True)

# # Save the plot with a timestamp in the 'result' folder
# timestamp = datetime.now().strftime('%Y%m%d%H%M%S')
# filename = f'result/result_{timestamp}.png'
# plt.savefig(filename)

# # Show the plot
# plt.show()