//
// Created by Eric Yan on 2021/5/12.
//

#ifndef RAYTRACING_RAY_H
#define RAYTRACING_RAY_H

#include "vec3.h"

class ray {
    public:
        ray() {}
        ray(const point3& origin, const vec3& direction) {
            this->orig = origin;
            this->dir = direction;
        }

        point3 origin() const { return this->orig; }
        vec3 direction() const { return this->dir; }

        point3 at(double times) const {
            return this->orig + this->dir * times;
        }

    public:
        point3 orig;
        vec3 dir;
};

#endif //RAYTRACING_RAY_H
