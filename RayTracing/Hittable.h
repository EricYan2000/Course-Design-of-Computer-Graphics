//
// Created by Eric Yan on 2021/5/25.
//

#ifndef RAYTRACING_HITTABLE_H
#define RAYTRACING_HITTABLE_H

#include "myRayTracing.h"
#include "vec3.h"
#include "ray.h"

class Material;

////the structure used to pass the hitting information
struct hit_record {
    point3 hit_point;
    vec3 normal;
    //Material& material;
    double distance;
    double u;
    double v;
    shared_ptr<Material> mat_ptr;
    bool front_face;

    ////@preset: outward_normal has to be a unit_vector to ensure that normal is a unit_vector
    inline void set_face_normal(const ray& r, const vec3& outward_normal) {
        // front_face: whether the ray r hits the object from the outside
        front_face = (dot(r.direction(), outward_normal) < 0);
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class Hittable {
    public:
        virtual bool hit(const ray& r, double min_distance, double max_distance, hit_record& rec) const = 0;
};

#endif //RAYTRACING_HITTABLE_H