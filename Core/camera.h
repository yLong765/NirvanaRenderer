//
// Created by yangyinlong01 on 2020/9/28.
//

#ifndef NIRVANARENDERER_CAMERA_H
#define NIRVANARENDERER_CAMERA_H

struct camera_t {
    vec3_t eye;
    vec3_t center;
    vec3_t up;
    float fovy;
    float near;
    float far;
};

camera_t *
create_camera(vec3_t eye, vec3_t center = {0, 0, 0}, vec3_t up = {0, 1, 0}, float fovy = deg2rad(60), float near = 1.0f,
              float far = 500.0f) {
    camera_t *camera = new camera_t();
    camera->eye = eye;
    camera->center = center;
    camera->fovy = fovy;
    camera->near = near;
    camera->far = far;
    return camera;
}

mat4_t get_view_matrix(camera_t *camera) {
    return mat4_look_at(camera->eye, camera->center);
}

mat4_t get_projection_matrix(camera_t *camera, float aspect) {
    return mat4_perspective(camera->fovy, aspect, camera->near, camera->far);
}

#endif //NIRVANARENDERER_CAMERA_H
