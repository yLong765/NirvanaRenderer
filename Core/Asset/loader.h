//
// Created by yangyinlong01 on 2020/9/29.
//

#ifndef NIRVANARENDERER_LOADER_H
#define NIRVANARENDERER_LOADER_H

class loader {
protected:
    vector<vec4_t> verts_, norms_;
    vector<vector<vec4_t>> faces_;

public:
    loader() : verts_(), norms_(), faces_() {}

    object* instantiate_object() {
        object* obj = new object();
        obj->initialize(verts_, norms_, faces_);
        return obj;
    }

    int face_size() { return faces_.size(); }

    vec4_t vert(int iface, int nthvert) { return verts_[faces_[iface][nthvert][0]]; }

    vec4_t normal(int iface, int nthvert) { return verts_[faces_[iface][nthvert][2]]; }
};

#endif //NIRVANARENDERER_LOADER_H
