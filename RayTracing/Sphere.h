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
        Sphere(point3 center, double radius, shared_ptr<Material> mat) {
            this->center = center;
            this->radius = radius;
            this->mat_ptr = mat;
        }

        virtual bool hit(const ray& r, double min_distance, double max_distance, hit_record& rec) const override;

    public:
        point3 center;
        double radius;
        shared_ptr<Material> mat_ptr;
};

////@preset: min_distance and max_distance should be larger than 0.
////@caution: only find the solution that is in front of the camera,
///           which means only consider t that is greater than 0
////@result: return whether this ray r hits this sphere. If yes, return hitting information through &rec
bool Sphere::hit(const ray& r, double min_distance, double max_distance, hit_record& rec) const {
    vec3 oc = this->center - r.origin();
    double a = dot(r.direction(), r.direction());
    double b = -2 * dot(oc, r.direction());
    double c = dot(oc, oc) - this->radius * this->radius;

    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        return false;
    } else {
        double t1 = (-b + sqrt(discriminant)) / (2 * a);
        double t2 = (-b - sqrt(discriminant)) / (2 * a);

        ////@condition: a is definitely larger than 0. So, t1 is larger than t2.
        ///             Thus, t2 is nearer than t1
        double root = t2;


        ////@TODO: desert solution that does not lie within (min_distance, max_distance)
        if (root < min_distance || root > max_distance) {
            root = t1;
            if (root < min_distance || root > max_distance)
                return false; //no root within in the desired range
        }

        rec.distance = root;
        rec.hit_point = r.at(root);
        rec.mat_ptr = this->mat_ptr;
        vec3 outward_normal = (r.at(root) - this->center) / radius;
        rec.set_face_normal(r, outward_normal);

        return true;
    }
}

#endif //RAYTRACING_SPHERE_H