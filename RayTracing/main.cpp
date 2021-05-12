#include <iostream>
#include "vec3.h"
#include "ray.h"
#include "color.h"
#include "MyCamera.h"

using namespace std;

void vector_test();
void stage_1();


color ray_color(const ray& r) {
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
}

int main() {
    //// Camera
    MyCamera myCamera(point3(0,0,0), point3(0,0,-2), vec3(0,1,0), 6, 6);


    //// Render
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    for (int j = image_height-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            double u = double(i)/(image_width-1);
            double v = double(j)/(image_height-1);
            ray r = myCamera.get_ray(u, v);
            color pixel_color = ray_color(r);
            write_color_stream(std::cout, pixel_color);
        }
    }
    std::cerr << "\nDone.\n";
}

void stage_1() {
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    for (int j = image_height-1; j >= 0; --j) {
        for (int i = 0; i < image_width; ++i) {
            auto r = double(i) / (image_width-1);
            auto g = double(j) / (image_height-1);
            auto b = 0.25;

            int ir = (int)(255.999 * r);
            int ig = (int)(255.999 * g);
            int ib = (int)(255.999 * b);

            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }
    return ;
}

void vector_test() {
    vec3 a(1, 2, 3), b(-4.5, 0, 2);
    std::cout << "Hello, World!" << std::endl;
    std::cout << "a is " << a << std::endl;
    std::cout << "b is " << b << std::endl;
    std::cout << "add " << a + b << std::endl;
    std::cout << "minus " << a - b << std::endl;
    std::cout << "dot " << dot(a, b) << std::endl;
    std::cout << "cross " << cross(a, b) << std::endl;
    std::cout << "3 times a is " << a * 3 << std::endl;
}
