//
// Created by Eric Yan on 2021/6/28.
//

#ifndef RAYTRACING_BOX_H
#define RAYTRACING_BOX_H

#include "myRayTracing.h"
#include "aarect.h"
#include "Hittable_list.h"
#include "Hittable.h"

//// box that is perpendicular to all 3 axis
class Box : public Hittable {
    public:
        Box() {}
        Box(const point3& p0, const point3& p1, shared_ptr<Material> ptr) {
            this->left_behind = p0;
            this->right_front = p1;

            //// adding 6 surfaces of a box
            sides.add(make_shared<xy_rect>(p0.x(), p1.x(), p0.y(), p1.y(), p1.z(), ptr));
            sides.add(make_shared<xy_rect>(p0.x(), p1.x(), p0.y(), p1.y(), p0.z(), ptr));

            sides.add(make_shared<xz_rect>(p0.x(), p1.x(), p0.z(), p1.z(), p1.y(), ptr));
            sides.add(make_shared<xz_rect>(p0.x(), p1.x(), p0.z(), p1.z(), p0.y(), ptr));

            sides.add(make_shared<yz_rect>(p0.y(), p1.y(), p0.z(), p1.z(), p1.x(), ptr));
            sides.add(make_shared<yz_rect>(p0.y(), p1.y(), p0.z(), p1.z(), p0.x(), ptr));
        }

        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

    public:
        point3 left_behind;
        point3 right_front;
        Hittable_list sides;
};

//// a ray hits this box once it hits any of the 6 surfaces
bool Box::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    return sides.hit(r, t_min, t_max, rec);
}

#endif //RAYTRACING_BOX_H
