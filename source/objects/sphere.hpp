#pragma once

#include <memory>
#include "hittable.hpp"
#include "material.hpp"

class sphere : public hittable {
 public:
  sphere() = default;
  sphere(point3 center, double radius, std::shared_ptr<material> m)
      : m_center(center), m_radius(radius), m_material_ptr(m){};

  auto hit(const ray& ray, double t_min, double t_max, hit_record& rec) const -> bool override;

 private:
  point3 m_center;
  double m_radius;
  std::shared_ptr<material> m_material_ptr;
};
