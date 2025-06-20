#include <cmath>
#include <iostream>
#include <memory>

#include "objects/sphere.hpp"
#include "rtweekend.hpp"
#include "libs/color.hpp"
#include "objects/hittable_list.hpp"

double hit_sphere(const point3& centre, double radius, const ray& r) {
  vec3 oc = r.origin() - centre;
  auto a = r.direction().length_squared(); // Vector Dotted to itself if just squared length.
  auto half_b = dot(r.direction(), oc);
  auto c = oc.length_squared() - radius * radius;
  auto discriminant = half_b * half_b -  a * c;
  if (discriminant >= 0) {
    // Use Quadratic formula to find the root, the root in this case will
    // help us find the hit point. Drawing a vector from centre to the hit
    // point will yeild us the surface normal.
    return (-half_b - sqrt(discriminant)) / (a);
  }

  // If discrimininat less than 0
  return -1.0;
}

auto ray_color(const ray& ray, const hittable& world) {
    hit_record rec;
    if(world.hit(ray, 0, infinity, rec)) {
        return 0.5 * (rec.normal + color(1,1,1));
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

  // World
  hittable_list world;
  world.add(std::make_shared<sphere>(point3(0,0,-1), 0.5));
  world.add(std::make_shared<sphere>(point3(0,-100.5,-1), 100));

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
      color pixel_color = ray_color(r, world);
      write_color(std::cout, pixel_color);
    }
  }

  std::cerr << "\nDone.\n";
  return 0;
}
