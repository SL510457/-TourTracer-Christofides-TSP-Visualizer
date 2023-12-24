from Christofides import calculate_tsp
import random

def generate_coordinates(num_cities, min_lat, max_lat, min_lon, max_lon):
    coordinates = []

    for _ in range(num_cities):
        lat = random.uniform(min_lat, max_lat)
        lon = random.uniform(min_lon, max_lon)
        coordinates.append((lat, lon))

    return coordinates

def test_calculate_tsp():
    coordinates = [(0, 0), (1, 1), (2, 2), (3, 3)]
    result = calculate_tsp(coordinates)
    assert result == 0

def test_generate_coordinates():
    num_cities = 5
    min_lat, max_lat = -90, 90
    min_lon, max_lon = -180, 180
    result = generate_coordinates(num_cities, min_lat, max_lat, min_lon, max_lon)

    assert len(result) == num_cities
    for lat, lon in result:
        assert min_lat <= lat <= max_lat
        assert min_lon <= lon <= max_lon