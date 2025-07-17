#pragma once

#include "hittable.hpp"
#include "material.hpp"

class metal : public material {
    public:
        color albedo;

        metal(const color& a) : albedo(a) {}
        virtual auto scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const -> bool override {
            vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
            scattered = ray(rec.p, reflected);
            attenuation = albedo;
            return (dot(scattered.direction(), rec.normal) > 0);
        }
};
