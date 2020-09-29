//
// Created by yangyinlong01 on 2020/9/29.
//

#ifndef NIRVANARENDERER_OBJECT_H
#define NIRVANARENDERER_OBJECT_H

class object {
    vector<vec4_t> verts_, norms_;
    vector<vector<vec4_t>> faces_;

public:
    transform_t *transform;

    void initialize(vector<vec4_t> verts, vector<vec4_t> norms, vector<vector<vec4_t>> faces) {
        verts_ = verts;
        norms_ = norms;
        faces_ = faces;
        transform = create_component<transform_t>();
    }

    int face_size() { return faces_.size(); }

    vec4_t vert(int iface, int nthvert) { return verts_[faces_[iface][nthvert][0]]; }

    vec4_t normal(int iface, int nthvert) { return verts_[faces_[iface][nthvert][2]]; }

    mat4_t get_transform_matrix() const {
        return transform->get_transform_matrix();
    }

    component_t *add_component(component_type type) {
        if (type == component_type::transform) {
            return create_component<transform_t>();
        }
    }
};

#endif //NIRVANARENDERER_OBJECT_H
