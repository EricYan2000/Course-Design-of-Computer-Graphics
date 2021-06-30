//
// Created by Eric Yan on 2021/6/27.
//

#ifndef RAYTRACING_AARECT_H
#define RAYTRACING_AARECT_H

#include "Hittable.h"

class xy_rect : public Hittable {
    public:
        xy_rect() {}

        xy_rect(double _x0, double _x1, double _y0, double _y1, double _k, shared_ptr<Material> mat) {
            this->x0 = _x0;
            this->x1 = _x1;
            this->y0 = _y0;
            this->y1 = _y1;
            this->k = _k;
            this->mat_ptr = mat;
        }

        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

    public:
        shared_ptr<Material> mat_ptr;
        double x0, x1, y0, y1, k;
};

class xz_rect : public Hittable {
    public:
        xz_rect() {}

        xz_rect(double _x0, double _x1, double _z0, double _z1, double _k, shared_ptr<Material> mat) {
            this->x0 = _x0;
            this->x1 = _x1;
            this->z0 = _z0;
            this->z1 = _z1;
            this->k = _k;
            this->mat_ptr = mat;
        }

        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

    public:
        shared_ptr<Material> mat_ptr;
        double x0, x1, z0, z1, k;
};

class yz_rect : public Hittable {
    public:
        yz_rect() {}

        yz_rect(double _y0, double _y1, double _z0, double _z1, double _k, shared_ptr<Material> mat) {
            this->y0 = _y0;
            this->y1 = _y1;
            this->z0 = _z0;
            this->z1 = _z1;
            this->k = _k;
            this->mat_ptr = mat;
        }

        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

    public:
        shared_ptr<Material> mat_ptr;
        double y0, y1, z0, z1, k;
};

bool xy_rect::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    auto t = (k - r.origin().z()) / r.direction().z();
    if (t < t_min || t > t_max)
        return false;

    auto x = r.origin().x() + t * r.direction().x();
    auto y = r.origin().y() + t * r.direction().y();
    if (x < x0 || x > x1 || y < y0 || y > y1)
        return false;

    rec.u = (x - x0) / (x1 - x0);
    rec.v = (y - y0) / (y1 - y0);
    rec.distance = t;
    auto outward_normal = vec3(0, 0, 1);
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = mat_ptr;
    rec.hit_point = r.at(t);

    return true;
}


bool xz_rect::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    auto t = (k - r.origin().y()) / r.direction().y();
    if (t < t_min || t > t_max)
        return false;

    auto x = r.origin().x() + t * r.direction().x();
    auto z = r.origin().z() + t * r.direction().z();
    if (x < x0 || x > x1 || z < z0 || z > z1)
        return false;

    rec.u = (x - x0) / (x1 - x0);
    rec.v = (z - z0) / (z1 - z0);
    rec.distance = t;
    auto outward_normal = vec3(0, 1, 0);
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = mat_ptr;
    rec.hit_point = r.at(t);

    return true;
}


bool yz_rect::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    auto t = (k - r.origin().x()) / r.direction().x();
    if (t < t_min || t > t_max)
        return false;

    auto y = r.origin().y() + t * r.direction().y();
    auto z = r.origin().z() + t * r.direction().z();
    if (y < y0 || y > y1 || z < z0 || z > z1)
        return false;

    rec.u = (y - y0) / (y1 - y0);
    rec.v = (z - z0) / (z1 - z0);
    rec.distance = t;
    auto outward_normal = vec3(1, 0, 0);
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = mat_ptr;
    rec.hit_point = r.at(t);

    return true;
}

#endif //RAYTRACING_AARECT_H
