#include <iostream>
#include "vec3.h"

using namespace std;

void vector_test();

int main() {
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height-1; j >= 0; --j) {
        for (int i = 0; i < image_width; ++i) {
            auto r = double(i) / (image_width-1);
            auto g = double(j) / (image_height-1);
            auto b = 0.25;

            int ir = static_cast<int>(255.999 * r);
            int ig = static_cast<int>(255.999 * g);
            int ib = static_cast<int>(255.999 * b);

            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }
    
    return 0;
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
