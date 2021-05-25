//
// Created by Eric Yan on 2021/5/25.
//

#ifndef RAYTRACING_HITTABLE
#define RAYTRACING_HITTABLE

#include "myRayTracing.h"
#include "vec3.h"
#include "ray.h"

class Material;

struct hit_record {
    point3 hit_point;
    vec3 normal;
    Material material;
    double distance;
    bool front_face;

    inline void set_face_nornal(const ray& r, const vec3& outward_norma) {
        // front_face: whether the ray r hits the object from the outside
        front_face = (dot(r, normal) < 0);
        normal = front_face ? outward_normal : -outward_normal;
    }
}

class Hittable {
    public:
        virtual bool hit(const ray& r, double min_distance, double max_distance, hit_record& rec) const = 0;
}

#endif //RAYTRACING_HITTABLE