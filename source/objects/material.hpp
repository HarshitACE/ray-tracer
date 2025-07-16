#pragma once

#include "../libs/ray.hpp"

struct hit_record;

class material {
 public:
  virtual ~material() = default;
  virtual auto scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const -> bool = 0;
};
