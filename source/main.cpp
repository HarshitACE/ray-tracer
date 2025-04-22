#include <iostream>

#include "libs/color.hpp"
#include "libs/ray.hpp"
#include "libs/vec3.hpp"

bool hit_sphere(const point3& centre, double radius, const ray& r) {
  // EQUATION FORMED:
  // (P - C) . (P - C) = r^2;  where P -> P(t) = A + tb
  // P -> P(t) = A + tb; A is the origin of the ray and b is the direction
  // t^2b.b - 2tb.(A-C) + (A-C).(A-C) - r^2 = 0
  //
  // Now to calculate if the sphere is ever hit by the ray all we have to do is make sure the discriminant
  // of the quadratic equation is > 0 (=0 will glance the sphere)
  vec3 oc = r.origin() - centre;
  auto a = dot(r.direction(), r.direction());
  auto b = 2.0 * dot(r.direction(), oc);
  auto c = dot(oc, oc) - radius * radius;
  auto discriminant = b * b - 4 * a * c;
  return (discriminant > 0);
}

auto ray_color(const ray& ray) {
  // If the ray hits sphere color it red
  if (hit_sphere(point3(0, 0, -1), 0.5, ray)) {
    return color(1, 0, 0);
  }
  vec3 unit_direction = unit_vector(ray.direction());
  auto t = 0.5 * (unit_direction.y() + 1.0);
  return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

auto main() -> int {
  // Image
  const auto aspect_ratio = 16.0 / 9.0;
  const int image_width = 400;
  const int image_height = static_cast<int>(image_width / aspect_ratio);
  const double blue_val = 0.25;

  // Camera
  auto viewport_height = 2.0;
  auto viewport_width = aspect_ratio * viewport_height;
  auto focal_length = 1.0;  // Distance between viewport plane and camera's orign

  point3 origin{0, 0, 0};
  vec3 horizontal{viewport_width, 0, 0};
  vec3 vertical{0, viewport_height, 0};
  auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3{0, 0, focal_length};

  // Render
  std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

  for (int j = image_height - 1; j >= 0; --j) {
    std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
    for (int i = 0; i < image_width; ++i) {
      auto u = static_cast<double>(i) / (image_width - 1);
      auto v = static_cast<double>(j) / (image_height - 1);
      ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
      color pixel_color = ray_color(r);
      write_color(std::cout, pixel_color);
    }
  }

  std::cerr << "\nDone.\n";
  return 0;
}
