//
// Created by yangyinlong01 on 2020/9/28.
//

#ifndef NIRVANARENDERER_TRANSFORM_H
#define NIRVANARENDERER_TRANSFORM_H

class transform_t : public component_t {
public:
    vec3_t position;
    vec3_t rotation;
    vec3_t scale;

    transform_t() {
        position = vec3_t::zero();
        rotation = vec3_t::zero();
        scale = vec3_t::one();
    }

    mat4_t get_transform_matrix() {
        mat4_t transform = mat4_t::identity();
        transform = translate_matrix(position);
        transform = transform * rotate_z_matrix(deg2rad(rotation.z));
        transform = transform * rotate_y_matrix(deg2rad(rotation.y));
        transform = transform * rotate_x_matrix(deg2rad(rotation.x));
        transform = transform * scale_matrix(scale);
        return transform;
    }
};

//transform_t *create_transform() {
//    transform_t *transform = new transform_t();
//    transform->scale = vec3_t::one();
//    return transform;
//}

#endif //NIRVANARENDERER_TRANSFORM_H
