#include <iostream>
#include "vec3.h"

using namespace std;

int main() {
    vec3 a(1, 2, 3), b(-4.5, 0, 2);
    std::cout << "Hello, World!" << std::endl;
    std::cout << "a is " << a << std::endl;
    std::cout << "b is " << b << std::endl;
    std::cout << "add " << a + b << std::endl;
    std::cout << "minus " << a - b << std::endl;
    std::cout << "dot " << dot(a, b) << std::endl;
    std::cout << "cross " << cross(a, b) << std::endl;
    std::cout << "3 times a is " << a * 3 << std::endl;
    return 0;
}
