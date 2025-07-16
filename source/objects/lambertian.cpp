#include "lambertian.hpp"

auto lambertian::scatter(const ray&  /*r_in*/, const hit_record& rec, color& attenuation,
                     ray& scattered) const -> bool {
  auto scatter_direction = rec.normal + random_unit_vector();

  // Catch degenrate scatter direction
  if (scatter_direction.near_zero()) {
      scatter_direction = rec.normal;
  }

  scattered = ray(rec.p, scatter_direction);
  attenuation = albedo;
  return true;
}
