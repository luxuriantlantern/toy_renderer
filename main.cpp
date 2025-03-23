//
// Created by clx on 25-3-18.
//

#include <memory>
#include "scene/cube.h"
#include "io/viewer.h"
#include "io/loader.h"

// Window dimensions
const unsigned int SCR_WIDTH = 2560;
const unsigned int SCR_HEIGHT = 2560;

int main()
{
    auto mviewer = std::make_shared<Viewer>(SCR_WIDTH, SCR_HEIGHT, CameraType::PERSPECTIVE, Shadertype::PHONG, "Cube Renderer");
//    auto mcube = std::make_shared<Cube>();
//    mcube->initialize();
//    mcube->setColor(glm::vec3{1.0f, 1.0f, 1.0f});
//    mcube->setModelMatrix(glm::vec3{0.0f, 0.0f, 0.0f});
//    mcube->setMaterial(glm::vec3 {1.0, 0.5f, 0.31f}, glm::vec3 {1.0f, 0.5f, 0.31f}, glm::vec3 {0.5f, 0.5f, 0.5f});
//    auto mscene = mviewer->getScene();
//    mscene->addObject(mcube);
    auto mscene = mviewer->getScene();
    auto mloader = std::make_shared<Loader>();
    const std::string path = "/media/ftc/G/code/toy_renderer/assets/cube.obj";
    auto mobject = mloader->loadOBJ(path);
    mobject->setColor(glm::vec3{1.0f, 1.0f, 1.0f});
    mobject->setModelMatrix(glm::vec3{0.0f, 0.0f, 0.0f});
    mobject->setMaterial(glm::vec3 {1.0, 0.5f, 0.31f}, glm::vec3 {1.0f, 0.5f, 0.31f}, glm::vec3 {0.5f, 0.5f, 0.5f});
    mobject->setup();
    mscene->addObject(mobject);


    // Render loop
    mviewer->mainloop();
    return 0;
}