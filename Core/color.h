//
// Created by yangyinlong01 on 2020/9/22.
//

#ifndef NIRVANARENDERE_COLOR_H
#define NIRVANARENDERE_COLOR_H

#include <string>

typedef struct color {
    UCHAR bgra[4];
    UCHAR bytespp;

    color() : bgra(), bytespp(1) {
        for (int i = 0; i < 4; i++) bgra[i] = 0;
    }

    color(UCHAR R, UCHAR G, UCHAR B, UCHAR A = 255) : bgra(), bytespp(4) {
        bgra[0] = B;
        bgra[1] = G;
        bgra[2] = R;
        bgra[3] = A;
    }

    color(UCHAR v) : bgra(), bytespp(1) {
        for (int i = 0; i < 4; i++) bgra[i] = 0;
        bgra[0] = v;
    }


    color(const UCHAR *p, UCHAR bpp) : bgra(), bytespp(bpp) {
        for (int i = 0; i < (int) bpp; i++) {
            bgra[i] = p[i];
        }
        for (int i = bpp; i < 4; i++) {
            bgra[i] = 0;
        }
    }

    UCHAR &operator[](const int i) { return bgra[i]; }

    color operator*(float intensity) const {
        color res = *this;
        intensity = (intensity > 1.f ? 1.f : (intensity < 0.f ? 0.f : intensity));
        for (int i = 0; i < 4; i++) res.bgra[i] = bgra[i] * intensity;
        return res;
    }

    std::string toString() {
        std::string str = "";
        for (size_t i = 0; i < 4; i++) {
            str += std::to_string((int) bgra[i]) + " ";
        }
        return str;
    }
} color_t;

#endif //NIRVANARENDERE_COLOR_H
