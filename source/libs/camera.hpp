#pragma once

#include "ray.hpp"
#include "vec3.hpp"

class camera {
 public:
  camera(point3 lookfrom, point3 lookat, vec3 vup,
         double vfov,  // Vertical field-of-view in degrees
         double aspect_ratio, double apeture, double focus_dist) {
    auto theta = degrees_to_radians(vfov);
    auto h = tan(theta / 2);
    auto viewport_height = 2.0 * h;
    auto viewport_width = aspect_ratio * viewport_height;

    w = unit_vector(lookfrom - lookat);
    u = unit_vector(cross(vup, w));
    v = cross(w, u);

    origin = lookfrom;
    horizontal = focus_dist * viewport_width * u;
    vertical = focus_dist * viewport_height * v;
    lower_left_corner = origin - horizontal / 2 - vertical / 2 - focus_dist * w;

    lens_radius = apeture / 2;
  }

  auto get_ray(double s, double t) const -> ray {
    vec3 rd = lens_radius * random_in_unit_disk();
    vec3 offset = u * rd.x() + v * rd.y();

    return {origin + offset, lower_left_corner + s * horizontal + t * vertical - origin - offset};
  }

 private:
  point3 origin;
  point3 lower_left_corner;
  vec3 horizontal;
  vec3 vertical;
  vec3 u, v, w;
  double lens_radius;
};
