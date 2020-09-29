//
// Created by yangyinlong01 on 2020/9/29.
//

#ifndef NIRVANARENDERER_COMPONENT_H
#define NIRVANARENDERER_COMPONENT_H

#include <api.h>

enum component_type
{
    transform,
};

class component_t {

};

template<class com>
com *create_component() {
    return new com();
}

#endif //NIRVANARENDERER_COMPONENT_H
