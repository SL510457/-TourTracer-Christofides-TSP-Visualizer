import math
 # import numpy as n
import matplotlib.pyplot as plt
import Christofides
import random
from datetime import datetime
import os
# from mpl_toolkits.mplot3d import Axes3D

# import matplotlib.pyplot as plt
# import numpy as np
# from mpl_toolkits.mplot3d import Axes3D
# import random

# # Assuming coordinates is a list of tuples (lat, lon)
# num_coordinates = 15
# coordinates = [(random.uniform(-90, 90), random.uniform(-180, 180)) for _ in range(num_coordinates)]

# # Convert latitude and longitude to Cartesian coordinates on a unit sphere
# latitudes, longitudes = zip(*coordinates)
# latitudes = np.radians(latitudes)
# longitudes = np.radians(longitudes)

# x = np.cos(latitudes) * np.cos(longitudes)
# y = np.cos(latitudes) * np.sin(longitudes)
# z = np.sin(latitudes)

# # Create a 3D plot
# fig = plt.figure()
# ax = fig.add_subplot(111, projection='3d')

# # Scatter plot of points on the sphere
# ax.scatter(x, y, z, c='r', marker='o')

# # Annotate each point with latitude, longitude, and node number
# for i, (lat, lon) in enumerate(coordinates):
#     ax.text(np.cos(np.radians(lat)) * np.cos(np.radians(lon)),
#             np.cos(np.radians(lat)) * np.sin(np.radians(lon)),
#             np.sin(np.radians(lat)), f'Node {i}\nLat: {lat:.2f}\nLon: {lon:.2f}', 
#             fontsize=8, color='black', ha='center')

# # Set axis labels
# ax.set_xlabel('X')
# ax.set_ylabel('Y')
# ax.set_zlabel('Z')

# # Set the aspect ratio to be equal
# ax.set_box_aspect([np.ptp(coord) for coord in [x, y, z]])

# timestamp = datetime.now().strftime('%Y%m%d%H%M%S')
# filename = f'result/result_{timestamp}_3d.png'
# plt.savefig(filename)

# # Show the plot
# plt.show()


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

# Plot coordinates
plt.figure(figsize=(6, 6))
plt.scatter(*zip(*coordinates), c='blue', label='Coordinates')

# Annotate each point with latitude, longitude, and node number
for i, (lat, lon) in enumerate(coordinates):
    plt.annotate(f'Node {i}\nLat: {lat:.2f}\nLon: {lon:.2f}', (lat, lon),
                 textcoords="offset points", xytext=(0, 5), ha='center', fontsize=8, color='black')

# Plot Hamiltonian path
hamiltonian_path_coordinates = [coordinates[i] for i in hamiltonian_path]

# Connect the points in the Hamiltonian path
hamiltonian_path_coordinates.append(hamiltonian_path_coordinates[0])  # Connect back to the starting point
hamiltonian_path_x, hamiltonian_path_y = zip(*hamiltonian_path_coordinates)
plt.plot(hamiltonian_path_x, hamiltonian_path_y, c='red', linestyle='-', linewidth=2, label='Hamiltonian Path')

# Annotate Hamiltonian path length
hamiltonian_path_length_str = f'Length: {hamiltonian_path_length:.2f}'
plt.annotate(hamiltonian_path_length_str, xy=(0.5, 0.95), xycoords='axes fraction', ha='center', fontsize=12, color='black')

# Set labels and legend
plt.title('Traveling Salesman Problem - Christofides Algorithm')
# plt.xlabel('Latitude')
# plt.ylabel('Longitude')
plt.legend()

# Hide axis labels and ticks
plt.xticks([])
plt.yticks([])

# Create the 'result' folder if it doesn't exist
os.makedirs('result', exist_ok=True)

# Save the plot with a timestamp in the 'result' folder
timestamp = datetime.now().strftime('%Y%m%d%H%M%S')
filename = f'result/result_{timestamp}.png'
plt.savefig(filename)


# Show the plot
plt.show()

# # Plot coordinates in 3D
# fig = plt.figure(figsize=(10, 8))
# ax = fig.add_subplot(111, projection='3d')  # Create a 3D subplot

# # Scatter plot for coordinates
# ax.scatter(*zip(*coordinates), c='blue', label='Coordinates')

# # Annotate each point with latitude, longitude, and node number
# for i, (lat, lon) in enumerate(coordinates):
#     ax.text(lat, lon, 0, f'Node {i}\nLat: {lat:.2f}\nLon: {lon:.2f}',
#             xytext=(0, 5), ha='center', fontsize=8, color='black')

# # Plot Hamiltonian path in 3D
# hamiltonian_path_coordinates = [coordinates[i] for i in hamiltonian_path]

# # Connect the points in the Hamiltonian path
# hamiltonian_path_coordinates.append(hamiltonian_path_coordinates[0])  # Connect back to the starting point
# hamiltonian_path_x, hamiltonian_path_y, _ = zip(*hamiltonian_path_coordinates)
# ax.plot(hamiltonian_path_x, hamiltonian_path_y, [0] * len(hamiltonian_path_coordinates), c='red', linestyle='-', linewidth=2, label='Hamiltonian Path')

# # Set labels and legend
# ax.set_title('Traveling Salesman Problem - Christofides Algorithm (3D)')
# ax.set_xlabel('Latitude')
# ax.set_ylabel('Longitude')
# ax.set_zlabel('Z')  # Adding a dummy Z-axis label for a 3D effect
# ax.legend()

# # Create the 'result' folder if it doesn't exist
# os.makedirs('result', exist_ok=True)

# # Save the plot with a timestamp in the 'result' folder
# timestamp = datetime.now().strftime('%Y%m%d%H%M%S')
# filename = f'result/result_{timestamp}_3d.png'
# plt.savefig(filename)

# # Show the 3D plot
# plt.show()