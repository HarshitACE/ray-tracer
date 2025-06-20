#include <cmath>

#include "hittable.hpp"
#include "sphere.hpp"

auto sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const -> bool {
  // EQUATION FORMED:
  // (P - C) . (P - C) = r^2;  where P -> P(t) = A + tb
  // P -> P(t) = A + tb; A is the origin of the ray and b is the direction
  // t^2b.b - 2tb.(A-C) + (A-C).(A-C) - r^2 = 0
  //
  // Now to calculate if the sphere is ever hit by the ray all we have to do is make sure the discriminant
  vec3 oc = r.origin() - m_center;
  auto a = r.direction().length_squared();
  auto half_b = dot(oc, r.direction());
  auto c = oc.length_squared() - m_radius * m_radius;

  auto discriminant = half_b * half_b - a * c;
  if (discriminant < 0) {
    return false;
  }
  auto sqrtd = sqrt(discriminant);

  // Find the nearest root that lies in the acceptable range.
  auto root = (-half_b - sqrtd) / a;
  if (root < t_min || t_max < root) {
    root = (-half_b + sqrtd) / a;
    if (root < t_min || t_max < root) {
      return false;
    }
  }

  rec.t = root;
  rec.p = r.at(rec.t);
  vec3 outward_normal = (rec.p - m_center) / m_radius;
  rec.set_face_normal(r, outward_normal);

  return true;
}
