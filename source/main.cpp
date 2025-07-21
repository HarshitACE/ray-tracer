#include <cmath>
#include <iostream>
#include <memory>

#include "libs/camera.hpp"
#include "libs/color.hpp"
#include "libs/vec3.hpp"
#include "objects/dielectric.hpp"
#include "objects/hittable_list.hpp"
#include "objects/lambertian.hpp"
#include "objects/metal.hpp"
#include "objects/sphere.hpp"

double hit_sphere(const point3& centre, double radius, const ray& r) {
  vec3 oc = r.origin() - centre;
  auto a = r.direction().length_squared();  // Vector Dotted to itself if just squared length.
  auto half_b = dot(r.direction(), oc);
  auto c = oc.length_squared() - radius * radius;
  auto discriminant = half_b * half_b - a * c;
  if (discriminant >= 0) {
    // Use Quadratic formula to find the root, the root in this case will
    // help us find the hit point. Drawing a vector from centre to the hit
    // point will yeild us the surface normal.
    return (-half_b - sqrt(discriminant)) / (a);
  }

  // If discrimininat less than 0
  return -1.0;
}

auto ray_color(const ray& r, const hittable& world, int depth) {
  hit_record rec;

  // Prevent against infinite recursion
  if (depth <= 0) {
    return color(0, 0, 0);
  }

  if (world.hit(r, 0.001, infinity, rec)) {
    ray scattered;
    color attenuation;
    if (rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
      return attenuation * ray_color(scattered, world, depth - 1);
    }
    return color(0, 0, 0);
  }

  vec3 unit_direction = unit_vector(r.direction());
  auto t = 0.5 * (unit_direction.y() + 1.0);
  return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

auto main() -> int {
  // Image
  const auto aspect_ratio = 16.0 / 9.0;
  const int image_width = 400;
  const int image_height = static_cast<int>(image_width / aspect_ratio);
  const int samples_per_pixel = 100;
  const int max_depth = 50;

  // World
  auto R = cos(pi/4);
  hittable_list world;

  // auto material_ground = std::make_shared<lambertian>(color(0.8, 0.8, 0.0));
  // auto material_center = std::make_shared<lambertian>(color(0.1, 0.2, 0.5));
  // auto material_left = std::make_shared<dielectric>(1.5);
  // auto material_right = std::make_shared<metal>(color(0.8, 0.6, 0.2), 0.0);
  auto material_left = std::make_shared<lambertian>(color(0, 0, 1));
  auto material_right = std::make_shared<lambertian>(color(1, 0, 0));

  // world.add(std::make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0, material_ground));
  // world.add(std::make_shared<sphere>(point3(0, 0, -1), 0.5, material_center));
  // world.add(std::make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
  // world.add(std::make_shared<sphere>(point3(-1.0, 0.0, -1.0), -0.4, material_left));
  // world.add(std::make_shared<sphere>(point3(1.0, 0.0, -1.0), 0.5, material_right));
  world.add(std::make_shared<sphere>(point3(-R, 0, -1), R, material_left));
  world.add(std::make_shared<sphere>(point3(R, 0, -1), R, material_right));

  // Camera
  camera cam(90.0, aspect_ratio);

  // Render
  std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

  for (int j = image_height - 1; j >= 0; --j) {
    std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
    for (int i = 0; i < image_width; ++i) {
      color pixel_color(0, 0, 0);
      for (int s = 0; s < samples_per_pixel; ++s) {
        auto u = (i + random_double()) / (image_width - 1);
        auto v = (j + random_double()) / (image_height - 1);
        ray r = cam.get_ray(u, v);
        pixel_color += ray_color(r, world, max_depth);
      }
      write_color(std::cout, pixel_color, samples_per_pixel);
    }
  }

  std::cerr << "\nDone.\n";
  return 0;
}
