//
// Created by Eric Yan on 2021/5/13.
//

#ifndef RAYTRACING_SIMPLE_MYCAMERA_H
#define RAYTRACING_SIMPLE_MYCAMERA_H

#include "vec3.h"
#include "ray.h"

class MyCamera
{
    public:
        MyCamera(point3 look_from, point3 look_at, vec3 vec_up, double viewport_width, double viewport_height) {
            this->look_from = look_from;

            this->vec_to = unit_vector(look_at - look_from);
            this->vec_right = unit_vector(cross(this->vec_to, vec_up));
            this->vec_up = unit_vector(cross(this->vec_right, this->vec_to));

            this->horizontal = viewport_width * vec_right;
            this->vertical = viewport_height * vec_up;
            this->left_down_corner = look_at - viewport_width / 2 * this->vec_right - viewport_height / 2 * this->vec_up;
        }

        ray get_ray(double i, double j);

    public:
        point3 look_from;
        vec3 vec_to;
        vec3 vec_up;
        vec3 vec_right;
        point3 left_down_corner;
        vec3 horizontal;
        vec3 vertical;
};

ray MyCamera::get_ray(double i, double j) { ////Precaution: i and j are double [0, 1)
    return ray(look_from, left_down_corner + i * horizontal + j * vertical - look_from);
}

#endif //RAYTRACING_SIMPLE_MYCAMERA_H
