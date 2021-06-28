#include <iostream>
#include "vec3.h"
#include "ray.h"
#include "color.h"
#include "MyCamera.h"
#include "Hittable_list.h"
#include "Sphere.h"
#include <omp.h>

class lambertian;

using namespace std;

void vector_test();
void stage_1();
color ray_color_stage_3(const ray& r, const Hittable& world);

color color_buffer[IMAGE_WIDTH][IMAGE_HEIGHT];

Hittable_list scene() {
    Hittable_list world;

    auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
    auto material_left   = make_shared<dielectric>(1.5);
    auto material_right  = make_shared<metal>(color(0.8, 0.6, 0.2), 0.0);

    world.add(make_shared<Sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<Sphere>(point3( 0.0,    0.0, -1.0),   0.5, material_center));
    world.add(make_shared<Sphere>(point3(-1.0,    0.0, -1.0),   0.5, material_left));
    world.add(make_shared<Sphere>(point3( 1.0,    0.0, -1.0),   0.5, material_right));

    return world;
}

color ray_color(const ray& r, const Hittable& world, int depth) {
    if (depth <= 0) {
        return color(0, 0, 0);
    }

    hit_record rec;

    if (world.hit(r, 0.001, infinity, rec)) {
        ray scattered_out;
        color attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered_out)) {
            return attenuation * ray_color(scattered_out, world, depth - 1);
        } else {
            return color(0, 0, 0);
        }
    } else {
        vec3 unit_direction = unit_vector(r.direction());
        auto t = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
    }
}

int main() {
    //// Camera
    MyCamera myCamera(point3(-3.5,2,5), point3(0,0,-2), vec3(0,1,0), VIEWPORT_WIDTH, VIEWPORT_WIDTH / IMAGE_WH_RATIO);

    //// World
    Hittable_list world = scene();

    //// Render
    const int nworker = omp_get_num_procs();
    #pragma omp parallel for num_threads(nworker) schedule(dynamic, 1)
    for (int j = IMAGE_HEIGHT - 1; j >= 0; --j) {
        for (int i = 0; i < IMAGE_WIDTH; ++i) {
            color pixel_color(0, 0, 0);
            for (int sample = 1; sample <= SAMPLES_PER_PIXEL; sample++) {
                double u = (i + random_double())/(IMAGE_WIDTH - 1);
                double v = (j + random_double())/(IMAGE_HEIGHT - 1);
                ray r = myCamera.get_ray(u, v);
                pixel_color += ray_color(r, world, DEPTH);
            }
            //write_color_stream_gamma2(std::cout, pixel_color / SAMPLES_PER_PIXEL);
            color_buffer[i][j] = pixel_color / SAMPLES_PER_PIXEL;
        }
    }
    std::cerr << "\nRender finished\n";

    //// Output
    std::cout << "P3\n" << IMAGE_WIDTH << ' ' << IMAGE_HEIGHT << "\n255\n";
    for (int j = IMAGE_HEIGHT - 1; j >= 0; --j) {
        std::cerr << "\r[Output]Scanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < IMAGE_WIDTH; ++i) {
            write_color_stream_gamma2(std::cout, color_buffer[i][j]);
        }
    }
    std::cerr << "\nOutput finished\n";
}


//// code of previous stages

color ray_color_stage_3(const ray& r, const Hittable& world) {
    vec3 unit_direction = unit_vector(r.direction());
    hit_record rec;

    if (world.hit(r, 0.001, infinity, rec)) {
        double coef = clamp(dot(unit_vector(-r.direction()), rec.normal), 0.0, 1.0);
        return coef * color(1.0, 1.0, 1.0);
    }

    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

void stage_1() {
    std::cout << "P3\n" << IMAGE_WIDTH << ' ' << IMAGE_HEIGHT << "\n255\n";
    for (int j = IMAGE_HEIGHT - 1; j >= 0; --j) {
        for (int i = 0; i < IMAGE_WIDTH; ++i) {
            auto r = double(i) / (IMAGE_WIDTH - 1);
            auto g = double(j) / (IMAGE_HEIGHT - 1);
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
