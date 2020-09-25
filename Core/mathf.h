//
// Created by yangyinlong01 on 2020/9/23.
//

#ifndef NIRVANARENDERE_MATHF_H
#define NIRVANARENDERE_MATHF_H

typedef struct {
    template<typename T>
    static T clamp(T num, T min, T max) { return (num < min) ? min : ((num > max) ? max : num); }

    template<typename T>
    static T lerp(T a, T b, float t) { return a + (b - a) * t; }
} math_t;

#endif //NIRVANARENDERE_MATHF_H
