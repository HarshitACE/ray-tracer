#ifndef RAY_H
#define RAY_H

#include "vec3.hpp"

class ray {
 public:
  point3 orig;
  vec3 dir;
  ray() = default;
  ray(const point3& origin, const vec3& direction)
      : orig(origin), dir(direction) {}

  auto origin() const -> point3 { return orig; }
  auto direction() const -> vec3 { return dir; }

  auto at(double t) const -> point3 { return orig + (t * dir); }
};
#endif
