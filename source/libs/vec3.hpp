#pragma once

#include <array>
#include <cmath>
#include <iostream>

#include "../rtweekend.hpp"

class vec3 {
 public:
  std::array<double, 3> e;

  vec3() : e{0, 0, 0} {}
  vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

  auto x() const -> double { return e[0]; }
  auto y() const -> double { return e[1]; }
  auto z() const -> double { return e[2]; }

  auto operator-() const -> vec3 { return {-e[0], -e[1], -e[2]}; }
  auto operator[](int i) const -> double { return e[i]; }
  auto operator[](int i) -> double& { return e[i]; }

  auto operator+=(const vec3& v) -> vec3& {
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
  }

  auto operator*=(double t) -> vec3& {
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
  }

  auto near_zero() const -> bool {
    // Return true if the vector is close to zero in all dimension
    const auto s = 1e-8;
    return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
  }

  auto operator/=(const double t) -> vec3& { return *this *= 1 / t; }

  auto length() const -> double { return std::sqrt(length_squared()); }

  auto length_squared() const -> double { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; }

  inline static auto random() -> vec3 { return vec3(random_double(), random_double(), random_double()); }

  inline static auto random(double min, double max) -> vec3 {
    return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
  }
};

// Type aliases so it can be used in different contexts with different names
using point3 = vec3;  // 3d Point
using color = vec3;   // Colour

// vec3 Utility Functions

inline auto operator<<(std::ostream& out, const vec3& v) -> std::ostream& {
  return out << v.e[0] << ' ' << v.e[1] << v.e[2];
}

inline auto operator+(const vec3& u, const vec3& v) -> vec3 {
  return {u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]};
}

inline auto operator-(const vec3& u, const vec3& v) -> vec3 {
  return {u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]};
}

inline auto operator*(const vec3& u, const vec3& v) -> vec3 {
  return {u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]};
}

inline auto operator*(double t, const vec3& v) -> vec3 {
  return {t * v.e[0], t * v.e[1], t * v.e[2]};
}

inline auto operator*(const vec3& v, double t) -> vec3 {
  return t * v;
}

inline auto operator/(vec3 v, double t) -> vec3 {
  return (1 / t) * v;
}

inline auto dot(const vec3& u, const vec3& v) -> double {
  return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

inline auto cross(const vec3& u, const vec3& v) -> vec3 {
  return {u.e[1] * v.e[2] - u.e[2] * v.e[1], u.e[2] * v.e[0] - u.e[0] * v.e[2], u.e[0] * v.e[1] - u.e[1] * v.e[0]};
}

inline auto unit_vector(vec3 v) -> vec3 {
  return v / v.length();
}

inline auto random_in_unit_sphere() -> vec3 {
  while (true) {
    auto rand_point = vec3::random(-1, 1);
    if (rand_point.length_squared() >= 1) {
      continue;
    }
    return rand_point;
  }
}

inline auto reflect(const vec3& v, const vec3& n) {
  return v - 2 * dot(v, n) * n;
}

inline auto random_unit_vector() -> vec3 {
  return unit_vector(random_in_unit_sphere());
}

inline auto random_in_hemisphere(const vec3& normal) -> vec3 {
  vec3 in_unit_sphere = random_in_unit_sphere();
  if (dot(in_unit_sphere, normal) > 0.0) {
    return in_unit_sphere;
  }
  return -in_unit_sphere;
}
