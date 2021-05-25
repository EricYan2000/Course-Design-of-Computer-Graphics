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
    public:
        Hittable_list() {}
        Hittable_list(Hittable object) {

        }

        virtual bool hit(const ray& r, double min_distance, double max_distance, hit_record& rec) const = 0;

    public:
        std::vector<Hittable> objects;
}

#endif //RAYTRACING_HITTABLE_LIST