//
// Created by Eric Yan on 2021/5/25.
//

#ifndef RAYTRACING_Hittable_H
#define RAYTRACING_Hittable_H

#include "myRayTracing.h"
#include "vec3.h"
#include "ray.h"
#include "Hittable.h"

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

class translate : public Hittable {
    public:
        translate(shared_ptr<Hittable> p, const vec3& displacement)
                : ptr(p), offset(displacement) {}

        virtual bool hit(
                const ray& r, double t_min, double t_max, hit_record& rec) const override;

    public:
        shared_ptr<Hittable> ptr;
        vec3 offset;
};

bool translate::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    ray moved_r(r.origin() - offset, r.direction());
    if (!ptr->hit(moved_r, t_min, t_max, rec))
        return false;

    rec.hit_point += offset;
    rec.set_face_normal(moved_r, rec.normal);

    return true;
}

class rotate_y : public Hittable {
    public:
        rotate_y(shared_ptr<Hittable> p, double angle);

        virtual bool hit(
                const ray& r, double t_min, double t_max, hit_record& rec) const override;

    public:
        shared_ptr<Hittable> ptr;
        double sin_theta;
        double cos_theta;
        //aabb bbox;
};

rotate_y::rotate_y(shared_ptr<Hittable> p, double angle) : ptr(p) {
    auto radians = degrees_to_radians(angle);
    sin_theta = sin(radians);
    cos_theta = cos(radians);
}

bool rotate_y::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    auto origin = r.origin();
    auto direction = r.direction();

    origin[0] = cos_theta * r.origin()[0] - sin_theta * r.origin()[2];
    origin[2] = sin_theta * r.origin()[0] + cos_theta * r.origin()[2];

    direction[0] = cos_theta * r.direction()[0] - sin_theta * r.direction()[2];
    direction[2] = sin_theta * r.direction()[0] + cos_theta * r.direction()[2];

    ray rotated_r(origin, direction);

    if (!ptr->hit(rotated_r, t_min, t_max, rec))
        return false;

    auto p = rec.hit_point;
    auto normal = rec.normal;

    p[0] =  cos_theta * rec.hit_point[0] + sin_theta * rec.hit_point[2];
    p[2] = -sin_theta * rec.hit_point[0] + cos_theta * rec.hit_point[2];

    normal[0] =  cos_theta * rec.normal[0] + sin_theta * rec.normal[2];
    normal[2] = -sin_theta * rec.normal[0] + cos_theta * rec.normal[2];

    rec.hit_point = p;
    rec.set_face_normal(rotated_r, normal);

    return true;
}

#endif //RAYTRACING_Hittable_H