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
        //// this function return whether the ray r hits this object within the range of [min_distance, max_distance]
        //// if yes, pass the hit_point information through rec
        virtual bool hit(const ray& r, double min_distance, double max_distance, hit_record& rec) const = 0;
};

//// coordinate translation
class translate : public Hittable {
    public:
        translate(shared_ptr<Hittable> p, const vec3& displacement) {
            this->ptr = p;
            this->offset = displacement;
        }

        virtual bool hit(
                const ray& r, double t_min, double t_max, hit_record& rec) const override;

    public:
        shared_ptr<Hittable> ptr;
        vec3 offset;
};

//// move the ray, instead of the object to decide whether a hitting occurs
//// this method introduces fewer calculation
bool translate::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    ray moved_r(r.origin() - offset, r.direction());
    if (!ptr->hit(moved_r, t_min, t_max, rec))
        return false;

    rec.hit_point += offset;
    rec.set_face_normal(moved_r, rec.normal);

    return true;
}

//// an object rotates according to the y axis
class rotate_y : public Hittable {
    public:
        rotate_y(shared_ptr<Hittable> p, double angle) {
            this->ptr = p;
            auto radians = degrees_to_radians(angle);
            this->sin_theta = sin(radians);
            this->cos_theta = cos(radians);
        }

        virtual bool hit(
                const ray& r, double t_min, double t_max, hit_record& rec) const override;

    public:
        shared_ptr<Hittable> ptr;
        double sin_theta;
        double cos_theta;
};

//// basic coordinates translation in rotation
//// [x']  =  [cos_theta    -sin_theta] [x]
//// [y']     [sin_theta     cos_theta] [y]
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