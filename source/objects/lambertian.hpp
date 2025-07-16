#pragma once

#include "hittable.hpp"
#include "material.hpp"

class lambertian : public material {
 public:
  color albedo;

  lambertian(const color& a) : albedo(a){};

  virtual ~lambertian() = default;

  virtual auto scatter(const ray& r_in, const hit_record& rec, color& attenuation,
                       ray& scattered) const -> bool override;
};
