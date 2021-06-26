//
// Created by Eric Yan on 2021/5/6.
//

#ifndef RAYTRACING_MYRAYTRACING_H
#define RAYTRACING_MYRAYTRACING_H

#include <cmath>
#include <limits>
#include <memory>
#include <cstdlib>
#include <random>

// Usings
using std::shared_ptr;
using std::make_shared;
using std::sqrt;

//// Mathematical Consts
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

//// Image
const double image_width = 512;
const double image_height = 396;
//const double image_width = 1024;
//const double image_height = 792;
const double ratio = image_width / image_height;
//const int samples_per_pixel = 10;
const int samples_per_pixel = 5;

//// @Caution: only positive doubles can be generated
inline double random_double() { //random number in [0.0, 1.0)
    /*if (wants_negative)
        return (rand() * 2.0 - RAND_MAX)/ (RAND_MAX + 1.0);
    else*/
    return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) {
    return random_double() * (max - min) + min;
}

inline double clamp(double input, double min, double max) {
    if (input < min)
        return min;
    else if (input > max)
        return max;
    else
        return input;
}

#endif //RAYTRACING_MYRAYTRACING_H
