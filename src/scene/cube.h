//
// Created by clx on 25-3-19.
// it is used for test before finishing the asset loader
//

#ifndef TOY_RENDERER_CUBE_H
#define TOY_RENDERER_CUBE_H

#include "object.h"

class Cube : public Object {
public:
    Cube();
    ~Cube() = default;
    void initialize();
};

#endif //TOY_RENDERER_CUBE_H