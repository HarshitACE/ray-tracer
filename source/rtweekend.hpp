#pragma once

#include <cmath>
#include <random>
#include <limits>

// Constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility functions
inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

inline auto random_double() -> double {
    // Returns a random real in [0, 1)
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

inline auto random_double(double min, double max) -> double {
    static std::uniform_real_distribution<double> distribution(min, max);
    static std::mt19937 generator;
    return distribution(generator);
}

inline auto clamp(double x, double min, double max) -> double {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}
