//
// Created by Eric Yan on 2021/5/25.
//

#ifndef RAYTRACING_MATERIAL_H
#define RAYTRACING_MATERIAL_H

#include "myRayTracing.h"
#include "vec3.h"
#include "ray.h"
#include "Hittable.h"

class hit_record;

class Material {
    public:
        virtual bool scatter(
                const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
        ) const = 0;

        virtual color emitted(const point3& p) const {
            return color(0,0,0);
        }
};

class lambertian : public Material {
    public:
        lambertian(const color& a) { albedo = a; }

        virtual bool scatter(
                const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
        ) const override {
            vec3 scatter_direction = rec.normal + random_unit_vector();

            if (scatter_direction.near_zero())
                scatter_direction = rec.normal;

            scattered = ray(rec.hit_point, scatter_direction);
            attenuation = albedo;
            return true;
        }

    public:
        color albedo;
};

class metal : public Material {
    public:
        metal(const color& c, double f) {
            this->color = c;
            this->fuzz = (f < 1.0 ? f : 1.0);
        }

        virtual bool scatter(
                const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
        ) const override {
            vec3 reflected_out = reflect(unit_vector(r_in.direction()), rec.normal);
            scattered = ray(rec.hit_point, reflected_out + fuzz * random_in_unit_sphere());
            attenuation = color;
            return (dot(scattered.direction(), rec.normal) > 0);
        }

    public:
        color color;
        double fuzz;
};

class dielectric : public Material {
    public:
        dielectric(double index_of_refraction) {
            this->index_of_refraction = index_of_refraction;
        }

        virtual bool scatter(
                const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
        ) const override {
            attenuation = color(1.0, 1.0, 1.0);
            vec3 unit_direction = unit_vector(r_in.direction());
            double refraction_ratio = rec.front_face ? (1.0 / this->index_of_refraction) : this->index_of_refraction;

            double cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0);
            double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

            ////@caution: total internal reflection may occur
            bool cannot_refract = refraction_ratio * sin_theta > 1.0;
            vec3 scattered_out;

            if (cannot_refract) { //total internal reflection
                scattered_out = reflect(unit_direction, rec.normal);
            } else { //refraction
                scattered_out = refract(unit_direction, rec.normal, refraction_ratio);
            }

            scattered = ray(rec.hit_point, scattered_out);
            return true;
        }

    public:
        double index_of_refraction;
};

class light : public Material {
    public:
        light(color light_color) {
            this->light_color = light_color;
        }

        virtual bool scatter(
                const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
        ) const override {
            return false;
        }

        virtual color emitted(const point3& p) const override {
            return this->light_color;
        }

    public:
        color light_color;
};

#endif //RAYTRACING_MATERIAL_H