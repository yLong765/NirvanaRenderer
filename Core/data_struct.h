//
// Created by yangyinlong01 on 2020/9/23.
//

#ifndef NIRVANARENDERE_DATA_STRUCT_H
#define NIRVANARENDERE_DATA_STRUCT_H

#include "mathf.h"
#include "vec.h"
#include "mat.h"

// other utility
vec operator*(const vec &v, const mat &m) {
    float X = v.x * m[0][0] + v.y * m[1][0] + v.z * m[2][0] + v.w * m[3][0];
    float Y = v.x * m[0][1] + v.y * m[1][1] + v.z * m[2][1] + v.w * m[3][1];
    float Z = v.x * m[0][2] + v.y * m[1][2] + v.z * m[2][2] + v.w * m[3][2];
    float W = v.x * m[0][3] + v.y * m[1][3] + v.z * m[2][3] + v.w * m[3][3];
    return {X, Y, Z, W};
}
// other utility

#include "transform.h"

#endif //NIRVANARENDERE_DATA_STRUCT_H
