//
// Created by Eric Yan on 2021/5/25.
//

#ifndef RAYTRACING_HITTABLE_LIST
#define RAYTRACING_HITTABLE_LIST

#include "myRayTracing.h"
#include "Hittable.h"
#include "ray.h"

#include <vector>

class Hittable_list : public Hittable {
    ////如果出问题了，看看是不是因为传过来的是引用
    public:
        Hittable_list() {}
        Hittable_list(Hittable& object_ptr) {
            objects.push_back(object_ptr);
        }

        void add(Hittable& object_ptr) {
            objects.push_back(object_ptr);
        }

        virtual bool hit(const ray& r, double min_distance, double max_distance, hit_record& rec) const = 0;

    public:
        std::vector<Hittable&> objects;
};

bool Hittable_list::hit(const ray& r, double min_distance, double max_distance, hit_record& rec) const {
    hit_record temp_rec;
    bool hit = false;
    double nearest_hit = max_distance;

    for (const Hittable& object_ptr : objects) {
        if (object_ptr.hit(r, min_distance, nearest_hit, temp_rec)) {
            hit = true;
            nearest_hit = temp_rec.distance;
            rec = temp_rec;
        }
    }
    return hit;
}

#endif //RAYTRACING_HITTABLE_LIST