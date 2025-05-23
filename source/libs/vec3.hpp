#ifndef VEC3_H
#define VEC3_H

#include <array>
#include <cmath>
#include <iostream>

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

  auto operator/=(const double t) -> vec3& { return *this *= 1 / t; }

  auto length() const -> double { return std::sqrt(length_squared()); }

  auto length_squared() const -> double { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; }
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
#endif
