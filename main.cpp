//
// Created by clx on 25-3-18.
//

#include <memory>
#include "scene/cube.h"
#include "ui/viewer.h"

// Window dimensions
const unsigned int SCR_WIDTH = 2560;
const unsigned int SCR_HEIGHT = 1440;

int main()
{
    auto mviewer = std::make_shared<Viewer>(SCR_WIDTH, SCR_HEIGHT, CameraType::PERSPECTIVE, Shadertype::DEFAULT, "Cube Renderer");
    auto mcube = std::make_shared<cube>();
    mcube->initialize();
    auto mscene = mviewer->getScene();
    mscene->addObject(mcube);
    // Render loop
    mviewer->mainloop();
    return 0;
}