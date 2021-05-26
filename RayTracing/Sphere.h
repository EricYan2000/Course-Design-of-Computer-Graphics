//
// Created by SAMSUNG on 2021/5/26.
//

#ifndef RAYTRACING_SPHERE_H
#define RAYTRACING_SPHERE_H

#include "Hittable.h"
#include "Material.h"
#include "vec3.h"

class Material;

class Sphere : public Hittable {
    public:
        Sphere() {}
        Sphere() {point3 center, double radius, Material& material} {
            this->center = center;
            this->radius = radius;
            this->material = material;
        }

        virtual bool hit(const ray& r, double min_distance, double max_distance, hit_record& rec) const = 0;

    public:
        point3 center;
        double radius;
        Material& material;
};

bool Sphere::hit(const ray& r, double min_distance, double max_distance, hit_record& rec) const {
    
}

#endif //RAYTRACING_SPHERE_H