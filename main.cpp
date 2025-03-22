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
    auto mviewer = std::make_shared<Viewer>(SCR_WIDTH, SCR_HEIGHT, CameraType::PERSPECTIVE, Shadertype::PHONG, "Cube Renderer");
    auto mcube = std::make_shared<Cube>();
    mcube->initialize();
    mcube->setColor(glm::vec3{1.0f, 1.0f, 1.0f});
    mcube->setModelMatrix(glm::vec3{0.0f, 0.0f, 0.0f});
    mcube->setMaterial(glm::vec3 {1.0, 0.5f, 0.31f}, glm::vec3 {1.0f, 0.5f, 0.31f}, glm::vec3 {0.5f, 0.5f, 0.5f});
    auto mscene = mviewer->getScene();
    mscene->addObject(mcube);
    // Render loop
    mviewer->mainloop();
    return 0;
}