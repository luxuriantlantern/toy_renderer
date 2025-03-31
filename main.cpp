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
    auto mviewer = std::make_shared<Viewer>(SCR_WIDTH, SCR_HEIGHT, CAM_TYPE,
                                                               Shadertype::PHONG, "Cube Renderer");
//    auto mscene = mviewer->getScene();
//    auto mloader = mviewer->getLoader();
//    auto objects = mloader->load("../assets/cube.obj");
//    objects->setColor(glm::vec3{1.0f, 1.0f, 1.0f});
//    objects->setModelMatrix(glm::vec3{0.0f, 0.0f, 0.0f});
//    objects->setMaterial(glm::vec3 {1.0, 0.5f, 0.31f}, glm::vec3 {1.0f, 0.5f, 0.31f}, glm::vec3 {0.5f, 0.5f, 0.5f});
//    objects->setup();
//    mscene->addObject(objects);
    // Render loop
    mviewer->mainloop();
    return 0;
}