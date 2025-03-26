//
// Created by clx on 25-3-18.
//

#include <memory>
#include "io/viewer.h"

unsigned int SCR_WIDTH = 2560;
unsigned int SCR_HEIGHT = 1920;
CameraType CAM_TYPE = CameraType::PERSPECTIVE;

int main()
{
    std::shared_ptr<Viewer> mviewer = std::make_shared<Viewer>(SCR_WIDTH, SCR_HEIGHT, CAM_TYPE,
                                                               Shadertype::PHONG, "Cube Renderer", "../assets/config.json");
    // Render loop
    mviewer->mainloop();
    return 0;
}