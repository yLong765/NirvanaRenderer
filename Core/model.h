//
// Created by yangyinlong01 on 2020/9/24.
//

#ifndef NIRVANARENDERE_MODEL_H
#define NIRVANARENDERE_MODEL_H

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include "maths.h"

using namespace std;

class Model {
    vector<vec4_t> verts_, norms_;
    vector<vector<vec4_t>> faces_;

public:
    transform_t *transform;

    Model(const char *filename) : verts_(), norms_(), faces_() {
        ifstream in;
        in.open(filename, ifstream::in);
        if (!in.is_open()) {
            cerr << "Error: " << strerror(errno);
        }
        string line;
        while (!in.eof()) {
            getline(in, line);
            istringstream iss(line.c_str());
            char trash;
            if (!line.compare(0, 2, "v ")) {
                iss >> trash;
                vec4_t v{0, 0, 0, 1};
                for (int i = 0; i < 3; i++) iss >> v[i];
                verts_.push_back(v);
            } else if (!line.compare(0, 3, "vn ")) {
                iss >> trash >> trash;
                vec4_t n{0, 0, 0, 1};
                for (int i = 0; i < 3; i++) iss >> n[i];
                norms_.push_back(n);
            } else if (!line.compare(0, 2, "f ")) {
                vector<vec4_t> f;
                vec4_t tmp;
                iss >> trash;
                while (iss >> tmp[0] >> trash >> tmp[1] >> trash >> tmp[2]) {
                    for (int i = 0; i < 3; i++) tmp[i]--; // in wavefront obj all indices start at 1, not zero
                    f.push_back(tmp);
                }
                faces_.push_back(f);
            }
        }
        printf("model loading finish\n");

        transform = create_transform();
    }

    int face_size() { return faces_.size(); }

    vec4_t vert(int iface, int nthvert) { return verts_[faces_[iface][nthvert][0]]; }

    vec4_t normal(int iface, int nthvert) { return verts_[faces_[iface][nthvert][2]]; }

    mat4_t get_transform_matrix() {
        return transform->get_transform_matrix();
    }
};

#endif //NIRVANARENDERE_MODEL_H
