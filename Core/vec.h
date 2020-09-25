//
// Created by yangyinlong01 on 2020/9/21.
//

#ifndef NIRVANARENDERE_VEC_H
#define NIRVANARENDERE_VEC_H

#include <cassert>
#include <cmath>
#include "mathf.h"

using namespace std;

typedef struct vec {
    float x, y, z, w;

    vec(float X = 0, float Y = 0, float Z = 0, float W = 1) : x(X), y(Y), z(Z), w(W) {}

    float &operator[](const size_t i) {
        assert(i < 4 && i >= 0);
        return (i == 0 ? x : (i == 1 ? y : (i == 2 ? z : w)));
    }

    const float &operator[](const size_t i) const {
        assert(i < 4 && i >= 0);
        return (i == 0 ? x : (i == 1 ? y : (i == 2 ? z : w)));
    }

    float norm() const;

    vec &normalize(float);

    std::string toString() {
        return "(" + to_string(x) + ", " + to_string(y) + ", " + to_string(z) + ", " + to_string(w) + ")";
    }

    void to_screen_point(int width, int height) {
        float rhw = 1.0f / w;
        x = (x * rhw + 1.0f) * width * 0.5f;
        y = (1.0f - y * rhw) * height * 0.5f;
        z = z * rhw;
        w = 1.0f;
    }

} vec_t;

vec_t operator*(vec_t v, const float &f) {
    for (size_t i = 3; i--; v[i] *= f);
    return v;
}

vec_t operator+(vec_t v1, const vec_t &v2) {
    for (size_t i = 3; i--; v1[i] += v2[i]);
    return v1;
}

vec_t operator-(vec_t v1, const vec_t &v2) {
    for (size_t i = 3; i--; v1[i] -= v2[i]);
    return v1;
}

float vec_dot(const vec_t &v1, const vec_t &v2) {
    float num = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    return num;
}

vec_t vec_cross(const vec_t v1, const vec_t v2) {
    float x, y, z;
    x = v1.y * v2.z - v1.z * v2.y;
    y = v1.z * v2.x - v1.x * v2.z;
    z = v1.x * v2.y - v1.y * v2.x;
    return {x, y, z};
}

vec_t vec_lerp(const vec_t v1, const vec_t v2, const float t) {
    float x, y, z;
    x = math_t::lerp(v1.x, v2.x, t);
    y = math_t::lerp(v1.y, v2.y, t);
    z = math_t::lerp(v1.z, v2.z, t);
    return {x, y, z};
}

float vec_t::norm() const { return (float) sqrt(x * x + y * y + z * z); }

vec_t &vec_t::normalize(float l = 1) {
    *this = (*this) * (l / norm());
    return *this;
}

#endif //NIRVANARENDERE_VEC_H
