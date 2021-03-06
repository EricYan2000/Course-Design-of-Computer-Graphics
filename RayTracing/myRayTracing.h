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
const double VIEWPORT_WIDTH = 600;

//// params for regular scnene preview
//#define IMAGE_WIDTH 512
//#define IMAGE_HEIGHT 396
//const int SAMPLES_PER_PIXEL = 50;
//const int DEPTH = 10;

//// params for regular scene high quality
//#define IMAGE_WIDTH 1024
//#define IMAGE_HEIGHT 792
//const int SAMPLES_PER_PIXEL = 500;
//const int DEPTH = 20;

//// params for cornel box preview
#define IMAGE_WIDTH 512
#define IMAGE_HEIGHT 512
const int SAMPLES_PER_PIXEL = 100;
const int DEPTH = 10;

//// params for cornel box middle quality
//#define IMAGE_WIDTH 512
//#define IMAGE_HEIGHT 512
//const int SAMPLES_PER_PIXEL = 2000;
//const int DEPTH = 10;

//// params for cornel box high quality
//#define IMAGE_WIDTH 512
//#define IMAGE_HEIGHT 512
//const int SAMPLES_PER_PIXEL = 20000;
//const int DEPTH = 10;

#define IMAGE_WH_RATIO (1.0 * IMAGE_WIDTH / IMAGE_HEIGHT)


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

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

#endif //RAYTRACING_MYRAYTRACING_H
