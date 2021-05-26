//
// Created by Eric Yan on 2021/5/25.
//

#ifndef RAYTRACING_COLOR_H
#define RAYTRACING_COLOR_H

#include "myRayTracing.h"
#include "Hittable.h"
#include "vec3.h"
#include "ray.h"

class Material {
    public:
        virtual bool scatter(
                const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
        ) const = 0;
};

#endif //RAYTRACING_COLOR_H