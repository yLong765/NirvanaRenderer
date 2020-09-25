//
// Created by yangyinlong01 on 2020/9/23.
//

#ifndef NIRVANARENDERE_TRANSFORM_H
#define NIRVANARENDERE_TRANSFORM_H

#include "mat.h"

#define PI 3.1415926f

typedef struct {
    mat_t world;        // 世界坐标变换
    mat_t view;         // 相机坐标变换
    mat_t projection;   // 投影变换
    mat_t transform;    // transform = world * view * projection
    float width, height;

    void init(int, int);

    void update();

} transform_t;

void transform_t::init(int w, int h) {
    float aspect = (float) w / (float) h;
    world.set_identity();
    view.set_identity();
    projection.set_perspective(PI * 0.5f, aspect, 1.0f, 500.0f);
    width = w;
    height = h;
    update();
}

void transform_t::update() {
    transform = world * view * projection;
}

#endif //NIRVANARENDERE_TRANSFORM_H
