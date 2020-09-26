//
// Created by yangyinlong01 on 2020/9/21.
//

#ifndef NIRVANARENDERE_MAT_H
#define NIRVANARENDERE_MAT_H

#include "vec.h"
#include <string>
#include <iostream>

using namespace std;

typedef struct mat {
    vec matrix[4]{};

    mat() {
        for (size_t i = 0; i < 4; i++)
            for (size_t j = 0; j < 4; matrix[i][j] = 0, j++);
    }

    vec &operator[](const size_t i) {
        assert(i < 4 && i >= 0);
        return matrix[i];
    }

    const vec &operator[](const size_t i) const {
        assert(i < 4 && i >= 0);
        return matrix[i];
    }

    string toString() {
        string r = "";
        for (size_t i = 0; i < 4; i++) {
            for (size_t j = 0; j < 4; j++) {
                r += to_string(matrix[i][j]);
                r += j != 3 ? " " : "\n";
            }
        }
        return r;
    }

    void set_identity() {
        for (size_t i = 0; i < 4; i++)
            for (size_t j = 0; j < 4; j++)
                matrix[i][j] = (i == j);
    }

    void set_zero() {
        for (size_t i = 0; i < 4; i++)
            for (size_t j = 0; j < 4; j++)
                matrix[i][j] = 0;
    }

    void set_translate(float x, float y, float z) {
        set_identity();
        matrix[3][0] = x;
        matrix[3][1] = y;
        matrix[3][2] = z;
    }

    void set_scale(float x, float y, float z) {
        set_identity();
        matrix[0][0] = x;
        matrix[1][1] = y;
        matrix[2][2] = z;
    }

    void set_rotate(float x, float y, float z, float theta) {
        float qsin = (float) sin(theta * 0.5f);
        float qcos = (float) cos(theta * 0.5f);
        vec_t vec = {x, y, z, 1.0f};
        float w = qcos;
        vec.normalize();
        x = vec.x * qsin;
        y = vec.y * qsin;
        z = vec.z * qsin;
        matrix[0][0] = 1 - 2 * y * y - 2 * z * z;
        matrix[1][0] = 2 * x * y - 2 * w * z;
        matrix[2][0] = 2 * x * z + 2 * w * y;
        matrix[0][1] = 2 * x * y + 2 * w * z;
        matrix[1][1] = 1 - 2 * x * x - 2 * z * z;
        matrix[2][1] = 2 * y * z - 2 * w * x;
        matrix[0][2] = 2 * x * z - 2 * w * y;
        matrix[1][2] = 2 * y * z + 2 * w * x;
        matrix[2][2] = 1 - 2 * x * x - 2 * y * y;
        matrix[0][3] = matrix[1][3] = matrix[2][3] = 0.0f;
        matrix[3][0] = matrix[3][1] = matrix[3][2] = 0.0f;
        matrix[3][3] = 1.0f;
    }

    void set_lookat(const vec eye, const vec at, const vec up) {
        vec xaxis, yaxis, zaxis;
        zaxis = (at - eye).normalize();
        xaxis = (vec_cross(up, zaxis)).normalize();
        yaxis = vec_cross(zaxis, xaxis);

        matrix[0][0] = xaxis.x;
        matrix[1][0] = xaxis.y;
        matrix[2][0] = xaxis.z;
        matrix[3][0] = -vec_dot(xaxis, eye);

        matrix[0][1] = yaxis.x;
        matrix[1][1] = yaxis.y;
        matrix[2][1] = yaxis.z;
        matrix[3][1] = -vec_dot(yaxis, eye);

        matrix[0][2] = zaxis.x;
        matrix[1][2] = zaxis.y;
        matrix[2][2] = zaxis.z;
        matrix[3][2] = -vec_dot(zaxis, eye);

        matrix[0][3] = matrix[1][3] = matrix[2][3] = 0.0f;
        matrix[3][3] = 1.0f;
    }

    void set_perspective(float fov, float aspect, float zn, float zf) {
        set_zero();
        float fax = 1.0f / (float) tan(fov * 0.5f);
        matrix[0][0] = (float) (fax / aspect);
        matrix[1][1] = (float) (fax);
        matrix[2][2] = zf / (zf - zn);
        matrix[3][2] = -zn * zf / (zf - zn);
        matrix[2][3] = 1;
    }

    void set_viewport(float width, float height) {
        set_identity();
        matrix[0][0] = width * 0.5
    }

    void viewport(int x, int y, int w, int h, float n, float f)
    {
        Viewport = Matrix::identity();
        Viewport[0][3] = x + w / 2.f;
        Viewport[1][3] = y + h / 2.f;
        Viewport[2][3] = (f + n) / 2.f;

        Viewport[0][0] = w / 2.f;
        Viewport[1][1] = h / 2.f;
        Viewport[2][2] = (f - n) / 2.f;
    }

} mat_t;

mat_t operator+(mat_t m1, const mat_t &m2) {
    for (size_t i = 0; i < 4; i++)
        for (size_t j = 0; j < 4; j++)
            m1[i][j] += m2[i][j];
    return m1;
}

mat_t operator-(mat_t m1, const mat_t &m2) {
    for (size_t i = 0; i < 4; i++)
        for (size_t j = 0; j < 4; j++)
            m1[i][j] -= m2[i][j];
    return m1;
}

mat_t operator*(const mat_t &m1, const mat_t &m2) {
    mat_t m;
    for (size_t i = 0; i < 4; i++)
        for (size_t j = 0; j < 4; j++)
            m[j][i] = m1[j][0] * m2[0][i] +
                      m1[j][1] * m2[1][i] +
                      m1[j][2] * m2[2][i] +
                      m1[j][3] * m2[3][i];
    return m;
}

mat_t operator*(mat_t m, const float &f) {
    for (size_t i = 0; i < 4; i++)
        for (size_t j = 0; j < 4; m[i][j] *= f, j++);
    return m;
}

#endif //NIRVANARENDERE_MAT_H
