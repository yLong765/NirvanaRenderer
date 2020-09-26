//
// Created by yangs on 2020/9/26.
//

#ifndef NIRVANARENDERER_MATHS_H
#define NIRVANARENDERER_MATHS_H

#include <assert.h>
#include <string>

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

    string toString() const {
        return "(" + to_string(x) + ", " + to_string(y) + ")";
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

    string toString() const {
        return "(" + to_string(x) + ", " + to_string(y) + ", " + to_string(z) + ")";
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

    string toString() const {
        return "(" + to_string(x) + ", " + to_string(y) + ", " + to_string(z) + ", " + to_string(w) + ")";
    }
};
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

    static mat<nrows, ncols> identity() {
        mat<nrows, ncols> ret;
        for (int i = nrows; i--;)
            for (int j = ncols; j--; ret[i][j] = (i == j));
        return ret;
    }

    string toString() const {
        string ret;
        for (int i = 0; i < nrows; i++)
            for (int j = 0; j < ncols; j++)
                ret += matrix[i][j] + (j == (ncols - 1) ? "\n" : " ");
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

#endif //NIRVANARENDERER_MATHS_H
