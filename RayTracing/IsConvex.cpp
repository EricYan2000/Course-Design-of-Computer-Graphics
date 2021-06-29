//
// Created by Eric Yan on 2021/6/29.
//

#include "vec3.h"

////@preset: 1. all points are passes into this function in the sequence of anti-clockwise
////         2. for any 3 points in sequence, they shall not be on a straight point
bool isConvex(vec3 points[]) {
    int total = sizeof(points) / sizeof(points[0]);

    if (total < 3) {
        printf("fewer than 3 vertexes, not a polygon\n");
        return false;
    }

    vec3 last_cross_product = cross(points[0] - points[total - 1], points[1] - points[total - 1]);
    vec3 this_cross_product;

    ////@caution: total - 1 times of compare is needed, since we have done once in line no. 17 & 18
    for (int i = 0; i < total - 1; i++) {
        this_cross_product = cross(points[i + 1] - points[i], points[i + 2] - points[i]);
        ////@caution: preset 2 guarantees that this_cross_product != 0
        if (dot(this_cross_product, last_cross_product) < 0) {
            return false;
        } else {
            last_cross_product = this_cross_product;
        }
    }
    return true;
}



