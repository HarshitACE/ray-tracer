#pragma once

#include "hittable.hpp"

class sphere : public hittable {
 public:
  sphere() = default;
  sphere(point3 center, double radius) : m_center(center), m_radius(radius){};

  auto hit(const ray& ray, double t_min, double t_max, hit_record& rec) const -> bool override;

 private:
  point3 m_center;
  double m_radius;
};
