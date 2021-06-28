//
// Created by Eric Yan on 2021/5/6.
//

#ifndef RAYTRACING_VEC3_H
#define RAYTRACING_VEC3_H

#include <iostream>
#include <cmath>
#include "myRayTracing.h"

using std::sqrt;
using std::fabs;

class vec3 {
    public:
        vec3() {e[0] = 0, e[1] = 0, e[2] = 0;}
        vec3(double x, double y, double z) {
            e[0] = x, e[1] = y, e[2] = z;
        }

        double x() const { return e[0]; }
        double y() const { return e[1]; }
        double z() const { return e[2]; }

        vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
        double operator[](int i) const { return e[i]; }
        double& operator[](int i) { return e[i]; }

        vec3& operator+=(const vec3 &v) {
            this->e[0] += v.e[0];
            this->e[1] += v.e[1];
            this->e[2] += v.e[2];
            return *this;
        }

        vec3& operator*=(const double t) {
            this->e[0] *= t;
            this->e[1] *= t;
            this->e[2] *= t;
            return *this;
        }

        vec3& operator/=(const double d) {
            return this->operator*=(1/d);
        }

        double length_squared() const {
            return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
        }

        double length() const {
            return sqrt(length_squared());
        }

        inline static vec3 random() {
            return vec3(random_double(), random_double(), random_double());
        }

        inline static vec3 random(double min, double max) {
            return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
        }

        bool near_zero() const {
            static double eps = 1e-8;
            return (fabs(e[0]) < eps) && (fabs(e[1]) < eps) && (fabs(e[2]) < eps);
        }

        std::string to_string() {
            return std::to_string(e[0]) + " " + std::to_string(e[1]) + " " + std::to_string(e[2]);
        }


    public:
        double e[3];
};

using point3 = vec3;
using color = vec3;

inline std::ostream& operator<<(std::ostream &out, const vec3 &v) {
    return out << "(" << v.e[0] << ", " << v.e[1] << ", " << v.e[2] << ")";
}

inline vec3 operator+(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(double t, const vec3 &v) {
    return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline vec3 operator*(const vec3 &v, double t) {
    return t * v;
}

inline vec3 operator/(vec3 v, double t) {
    return (1/t) * v;
}

inline double dot(const vec3 &u, const vec3 &v) {
    return u.e[0] * v.e[0]
           + u.e[1] * v.e[1]
           + u.e[2] * v.e[2];
}

inline vec3 cross(const vec3 &u, const vec3 &v) {
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 unit_vector(vec3 v) {
    return v / v.length();
}

////@result: return a vector enclosed in the unit sphere
vec3 random_in_unit_sphere() {
    while(true) {
        vec3 vec = vec3::random(-1, 1);
        if (vec.length() < 1)
            return vec;
    }
}

vec3 random_unit_vector() {
    return unit_vector(random_in_unit_sphere());
}

vec3 reflect(const vec3& v_in, const vec3& normal) {
    return v_in - 2 * dot(v_in, normal) * normal;
}

vec3 refract(const vec3 v_in, const vec3& normal, double refraction_coef_ratio) {
    double cos_theta = clamp(dot(-v_in, normal), -1.0, 1.0);
    vec3 v_out_perpendicular = refraction_coef_ratio * (v_in + normal * cos_theta);
    vec3 v_out_parallel = -sqrt(fabs(1.0 - v_out_perpendicular.length_squared())) * normal;
    return v_out_parallel + v_out_perpendicular;
}

#endif //RAYTRACING_VEC3_H
