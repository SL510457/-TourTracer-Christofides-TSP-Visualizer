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