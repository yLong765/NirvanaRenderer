//
// Created by yangs on 2020/9/26.
//

#ifndef NIRVANARENDERER_MATHS_H
#define NIRVANARENDERER_MATHS_H

#include <cassert>
#include <string>
#include <cmath>

using namespace std;

////////////////////////////Vector////////////////////////////////////

template<int n>
struct vec {
    float data[n] = {0};

    vec() = default;

    float &operator[](const int i) {
        assert(i >= 0 && i < n);
        return data[i];
    }

    float operator[](const int i) const {
        assert(i >= 0 && i < n);
        return data[i];
    }
};

// vec mul vec
template<int n>
float operator*(const vec<n> &lhs, const vec<n> &rhs) {
    float ret = 0;
    for (int i = n; i--; ret += lhs[i] * rhs[i]);
    return ret;
}

// vec add vec
template<int n>
vec<n> operator+(const vec<n> &lhs, const vec<n> &rhs) {
    vec<n> ret = lhs;
    for (int i = n; i--; ret[i] += rhs[i]);
    return ret;
}

// vec sub vec
template<int n>
vec<n> operator-(const vec<n> &lhs, const vec<n> &rhs) {
    vec<n> ret = lhs;
    for (int i = n; i--; ret[i] -= rhs[i]);
    return ret;
}

// vec mul cont
template<int n>
vec<n> operator*(const vec<n> &lhs, const float &rhs) {
    vec<n> ret = lhs;
    for (int i = n; i--; ret[i] *= rhs);
    return ret;
}

template<int n>
vec<n> operator*(const float &lhs, const vec<n> &rhs) {
    vec<n> ret = rhs;
    for (int i = n; i--; ret[i] *= lhs);
    return ret;
}

// vec div cont
template<int n>
vec<n> operator/(const vec<n> &lhs, const float &rhs) {
    vec<n> ret = lhs;
    for (int i = n; i--; ret[i] /= rhs);
    return ret;
}

template<>
struct vec<2> {
    float x, y;

    vec() = default;

    vec(float X, float Y) : x(X), y(Y) {}

    float &operator[](const int i) {
        assert(i >= 0 && i < 2);
        return i == 0 ? x : y;
    }

    float operator[](const int i) const {
        assert(i >= 0 && i < 2);
        return i == 0 ? x : y;
    }

    string toString() const {
        return "(" + to_string(x) + ", " + to_string(y) + ")";
    }

    vec<2> &normalize() {
        (*this) = (*this) / sqrt((*this) * (*this));
        return (*this);
    }
};

template<>
struct vec<3> {
    float x, y, z;

    vec() = default;

    vec(float X, float Y, float Z) : x(X), y(Y), z(Z) {}

    float &operator[](const int i) {
        assert(i >= 0 && i < 3);
        return i == 0 ? x : (i == 1 ? y : z);
    }

    float operator[](const int i) const {
        assert(i >= 0 && i < 3);
        return i == 0 ? x : (i == 1 ? y : z);
    }

    string toString() const {
        return "(" + to_string(x) + ", " + to_string(y) + ", " + to_string(z) + ")";
    }

    vec<3> &normalize() {
        (*this) = (*this) / sqrt((*this) * (*this));
        return (*this);
    }

    static vec<3> one() {
        return {1, 1, 1};
    }
};

template<>
struct vec<4> {
    float x, y, z, w;

    vec() = default;

    vec(float X, float Y, float Z, float W = 1) : x(X), y(Y), z(Z), w(W) {}

    float &operator[](const int i) {
        assert(i >= 0 && i < 4);
        return i == 0 ? x : (i == 1 ? y : (i == 2 ? z : w));
    }

    float operator[](const int i) const {
        assert(i >= 0 && i < 4);
        return i == 0 ? x : (i == 1 ? y : (i == 2 ? z : w));
    }

    string toString() const {
        return "(" + to_string(x) + ", " + to_string(y) + ", " + to_string(z) + ", " + to_string(w) + ")";
    }

    vec<4> &normalize() {
        (*this) = (*this) / sqrt((*this) * (*this));
        return (*this);
    }

    void to_viewport(int width, int height) {
        float rhw = 1.0f / w;
        x = (x * rhw + 1) * 0.5f * width;
        y = (y * rhw + 1) * 0.5f * height;
        z = (z * rhw + 1) * 0.5f;
        w = 1.0f;
    }
};

vec<3> vec3_cross(const vec<3> &lhs, const vec<3> &rhs) {
    float x = lhs.y * rhs.z - lhs.z * rhs.y;
    float y = lhs.z * rhs.x - lhs.x * rhs.z;
    float z = lhs.x * rhs.y - lhs.y * rhs.x;
    return vec<3>{x, y, z};
}

////////////////////////////Vector////////////////////////////////////

////////////////////////////Matrix////////////////////////////////////

template<int nrows, int ncols>
struct mat {
    vec<ncols> matrix[nrows] = {{}};

    mat() = default;

    vec<ncols> &operator[](const int i) {
        assert(i >= 0 && i < nrows);
        return matrix[i];
    }

    vec<ncols> operator[](const int i) const {
        assert(i >= 0 && i < nrows);
        return matrix[i];
    }

    static mat<nrows, ncols> identity() {
        mat<nrows, ncols> ret;
        for (int i = nrows; i--;)
            for (int j = ncols; j--; ret[i][j] = (i == j));
        return ret;
    }

    static mat<nrows, ncols> zero() {
        mat<nrows, ncols> ret;
        for (int i = nrows; i--;)
            for (int j = ncols; j--; ret[i][j] = 0);
        return ret;
    }

    string toString() const {
        string ret;
        for (int i = 0; i < nrows; i++)
            for (int j = 0; j < ncols; j++)
                ret += to_string(matrix[i][j]) + (j == (ncols - 1) ? "\n" : " ");
        return ret;
    }
};

// mat mul vec
template<int nrows, int ncols>
vec<nrows> operator*(const mat<nrows, ncols> &lhs, const vec<ncols> &rhs) {
    vec<nrows> ret;
    for (int i = nrows; i--; ret[i] = lhs[i] * rhs);
    return ret;
}

// mat mul mat
template<int R1, int C1, int C2>
mat<R1, C2> operator*(const mat<R1, C1> &lhs, const mat<C1, C2> &rhs) {
    mat<R1, C2> ret;
    for (int i = R1; i--;)
        for (int j = C2; j--;)
            for (int k = C1; k--;)
                ret[i][j] += lhs[i][k] * rhs[k][j];
    return ret;
}

// mat mul cont
template<int nrows, int ncols>
mat<nrows, ncols> operator*(const mat<nrows, ncols> &lhs, const float &rhs) {
    mat<nrows, ncols> ret = lhs;
    for (int i = nrows; i--; ret[i] *= rhs);
    return ret;
}

// mat div cont
template<int nrows, int ncols>
mat<nrows, ncols> operator/(const mat<nrows, ncols> &lhs, const float &rhs) {
    mat<nrows, ncols> ret = lhs;
    for (int i = nrows; i--; ret[i] /= rhs);
    return ret;
}

// mat add mat
template<int nrows, int ncols>
mat<nrows, ncols> operator+(const mat<nrows, ncols> &lhs, const mat<nrows, ncols> &rhs) {
    mat<nrows, ncols> ret = lhs;
    for (int i = nrows; i--; ret[i] += rhs[i]);
    return ret;
}

// mat sub mat
template<int nrows, int ncols>
mat<nrows, ncols> operator-(const mat<nrows, ncols> &lhs, const mat<nrows, ncols> &rhs) {
    mat<nrows, ncols> ret = lhs;
    for (int i = nrows; i--; ret[i] -= rhs[i]);
    return ret;
}

////////////////////////////Matrix////////////////////////////////////

typedef vec<2> vec2_t;
typedef vec<3> vec3_t;
typedef vec<4> vec4_t;

typedef mat<3, 3> mat3_t;
typedef mat<4, 4> mat4_t;

////////////////////////////Translate////////////////////////////////////

/*
 * eye: the position of the eye point
 * center: the position of the target point
 * up: the direction of the up vector
 *
 * x_axis.x  x_axis.y  x_axis.z  -dot(x_axis,eye)
 * y_axis.x  y_axis.y  y_axis.z  -dot(y_axis,eye)
 * z_axis.x  z_axis.y  z_axis.z  -dot(z_axis,eye)
 *        0         0         0                 1
 *
 * z_axis: normalize(eye-target), the backward vector
 * x_axis: normalize(cross(up,z_axis)), the right vector
 * y_axis: cross(z_axis,x_axis), the up vector
 *
 * see http://www.songho.ca/opengl/gl_camera.html
 */
mat4_t mat4_look_at(const vec3_t eye, const vec3_t center, const vec3_t up = {0, 1, 0}) {
    vec3_t z_axis = (eye - center).normalize();
    vec3_t x_axis = vec3_cross(up, z_axis).normalize();
    vec3_t y_axis = vec3_cross(z_axis, x_axis);
    mat4_t matrix = mat4_t::identity();

    matrix[0][0] = x_axis.x;
    matrix[0][1] = x_axis.y;
    matrix[0][2] = x_axis.z;
    matrix[0][3] = -(x_axis * eye);

    matrix[1][0] = y_axis.x;
    matrix[1][1] = y_axis.y;
    matrix[1][2] = y_axis.z;
    matrix[1][3] = -(y_axis * eye);

    matrix[2][0] = z_axis.x;
    matrix[2][1] = z_axis.y;
    matrix[2][2] = z_axis.z;
    matrix[2][3] = -(z_axis * eye);

    return matrix;
}

/*
 * fovy: y方向的视角(单位为弧度)
 * aspect: 宽高比
 * near, far: 近远深度裁剪平面的距离
 *
 * 1/(aspect*tan(fovy/2))              0             0           0
 *                      0  1/tan(fovy/2)             0           0
 *                      0              0  -(f+n)/(f-n)  -2fn/(f-n)
 *                      0              0            -1           0
 *
 * this is the same as
 *     float half_h = near * (float)tan(fovy / 2);
 *     float half_w = half_h * aspect;
 *     mat4_frustum(-half_w, half_w, -half_h, half_h, near, far);
 *
 * see http://www.songho.ca/opengl/gl_projectionmatrix.html
 */
mat4_t mat4_perspective(float fovy, float aspect, float near, float far) {
    float z_range = far - near;
    mat4_t matrix = mat4_t::zero();
    assert(fovy > 0 && aspect > 0);
    assert(near > 0 && far > 0 && z_range > 0);
    matrix[1][1] = 1 / (float) tan(fovy * 0.5f);
    matrix[0][0] = matrix[1][1] / aspect;
    matrix[2][2] = -(far + near) / z_range;
    matrix[2][3] = -2 * far * near / z_range;
    matrix[3][2] = -1;
    return matrix;
}

/*
 * width: 场景宽度
 * height: 场景高度
 * ndc_point: NDC格式中的点
 *
 * x = [-1, 1] -> [0, w]
 * y = [-1, 1] -> [0, h]
 * z = [-1, 1] -> [0, 1]
 *
 * https://www.khronos.org/registry/OpenGL/specs/es/2.0/es_full_spec_2.0.pdf
 */
vec4_t viewport_transform(int width, int height, vec4_t ndc_point) {
    float rhw = 1.0f / ndc_point.w;
    float x = (ndc_point.x * rhw + 1) * 0.5f * width;
    float y = (ndc_point.y * rhw + 1) * 0.5f * height;
    float z = (ndc_point.z * rhw + 1) * 0.5f;
    return {x, y, z};
}

mat4_t translate_matrix(vec3_t v) {
    mat4_t matrix = mat4_t::identity();
    matrix[0][3] = v.x;
    matrix[1][3] = v.y;
    matrix[2][3] = v.z;
    return matrix;
}

mat4_t scale_matrix(vec3_t v) {
    mat4_t matrix = mat4_t::identity();
    assert(v.x != 0 && v.y != 0 && v.z != 0);
    matrix[0][0] = v.x;
    matrix[1][1] = v.y;
    matrix[2][2] = v.z;
    return matrix;
}

mat4_t rotate_x_matrix(float angle) {
    float c = (float)cos(angle);
    float s = (float)sin(angle);
    mat4_t matrix = mat4_t::identity();
    matrix[1][1] = c;
    matrix[1][2] = -s;
    matrix[2][1] = s;
    matrix[2][2] = c;
    return matrix;
}

mat4_t rotate_y_matrix(float angle) {
    float c = (float)cos(angle);
    float s = (float)sin(angle);
    mat4_t matrix = mat4_t::identity();
    matrix[0][0] = c;
    matrix[0][2] = s;
    matrix[2][0] = -s;
    matrix[2][2] = c;
    return matrix;
}

mat4_t rotate_z_matrix(float angle) {
    float c = (float)cos(angle);
    float s = (float)sin(angle);
    mat4_t matrix = mat4_t::identity();
    matrix[0][0] = c;
    matrix[0][1] = -s;
    matrix[1][0] = s;
    matrix[1][1] = c;
    return matrix;
}

////////////////////////////Translate////////////////////////////////////

#endif //NIRVANARENDERER_MATHS_H
