#pragma once

#include "hittable.hpp"
#include "material.hpp"

class dielectric : public material {
 public:
  double ir;  // Index of Refraction

  dielectric(double index_of_refraction) : ir(index_of_refraction) {}
  virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
    attenuation = color(1.0, 1.0, 1.0);
    double refraction_ratio = rec.front_face ? (1.0 / ir) : ir;
    vec3 unit_direction = unit_vector(r_in.direction());
    vec3 refracted = refract(unit_direction, rec.normal, refraction_ratio);
    scattered = ray(rec.p, refracted);
    return true;
  }
};
