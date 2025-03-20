//
// Created by clx on 25-3-20.
//

#ifndef VIEWER_H
#define VIEWER_H

#include "../camera/orthographic.h"
#include "../camera/perspective.h"

class Viewer {
public:
    Viewer();
    ~Viewer() = default;

    void init(int width, int height, CameraType type, const char* title);
    void mainloop();
};



#endif //VIEWER_H
