cmake_minimum_required(VERSION 3.17)
project(RayTracing)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXE_LINKER_FLAGS -static)
set(CMAKE_CXX_FLAGS "-fopenmp")

add_executable(RayTracing main.cpp vec3.h myRayTracing.h ray.h MyCamera.h color.h
                Hittable.h Hittable_list.h Material.h Sphere.h aarect.h Box.h)