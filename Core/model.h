//
// Created by yangyinlong01 on 2020/9/24.
//

#ifndef NIRVANARENDERE_MODEL_H
#define NIRVANARENDERE_MODEL_H

#include <vector>
#include "vec.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

class Model {
    std::vector<vec_t> verts_, norms_;
    std::vector<std::vector<vec_t>> faces_;

public:
    Model(const char *filename) : verts_(), norms_(), faces_() {
        std::ifstream in;
        in.open(filename, std::ifstream::in);
        if (!in.is_open()){
            std::cerr << "Error: " << std::strerror(errno);
        }
        std::string line;
        while (!in.eof()) {
            std::getline(in, line);
            std::istringstream iss(line.c_str());
            char trash;
            if (!line.compare(0, 2, "v ")) {
                iss >> trash;
                vec_t v;
                for (int i = 0; i < 3; i++) iss >> v[i];
                verts_.push_back(v);
            } else if (!line.compare(0, 3, "vn ")) {
                iss >> trash >> trash;
                vec_t n;
                for (int i = 0; i < 3; i++) iss >> n[i];
                norms_.push_back(n);
            } else if (!line.compare(0, 2, "f ")) {
                std::vector<vec_t> f;
                vec_t tmp;
                iss >> trash;
                while (iss >> tmp[0] >> trash >> tmp[1] >> trash >> tmp[2]) {
                    for (int i = 0; i < 3; i++) tmp[i]--; // in wavefront obj all indices start at 1, not zero
                    f.push_back(tmp);
                }
                faces_.push_back(f);
            }
        }
        printf("model loading finish\n");
    }

    int face_size() { return faces_.size(); }

    vec_t vert(int iface, int nthvert) { return verts_[faces_[iface][nthvert][0]]; }

    vec_t normal(int iface, int nthvert) { return verts_[faces_[iface][nthvert][2]]; }
};

#endif //NIRVANARENDERE_MODEL_H
