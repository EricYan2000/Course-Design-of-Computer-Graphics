//
// Created by Eric Yan on 2021/5/13.
//

#ifndef RAYTRACING_COLOR_H
#define RAYTRACING_COLOR_H

#include "vec3.h"

#include <iostream>

void write_color_stream(std::ostream &out, color pixel_color) {
    // Write the translated [0,255] value of each color component.
    out << (int)(255.999 * pixel_color.x()) << ' '
        << (int)(255.999 * pixel_color.y()) << ' '
        << (int)(255.999 * pixel_color.z()) << '\n';
}

void write_color_stream_gamma2(std::ostream &out, color pixel_color) {
    //// gamma 2 modification
    out << (int)(255.999 * clamp(sqrt(pixel_color.x()), 0.0, 1.0)) << ' '
        << (int)(255.999 * clamp(sqrt(pixel_color.y()), 0.0, 1.0)) << ' '
        << (int)(255.999 * clamp(sqrt(pixel_color.z()), 0.0, 1.0)) << '\n';
}

void write_color_printf(color pixel_color) {
    printf("%d %d %d\n", 255.999 * pixel_color.x(),
           255.999 * pixel_color.y(), 255.999 * pixel_color.z());
}

#endif //RAYTRACING_COLOR_H
