//
// Created by clx on 25-3-18.
//

#include <memory>
#include "scene/cube.h"
#include "io/viewer.h"
#include "io/loader.h"
#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>

// Window dimensions
unsigned int SCR_WIDTH = 2560;
unsigned int SCR_HEIGHT = 1920;
CameraType CAM_TYPE = CameraType::PERSPECTIVE;
int fx, fy, cx, cy;

void loadJSON(const std::string &path)
{
    std::ifstream file(path);
    if(!file.is_open())
    {
        std::cerr << "Failed to open file: " << path << std::endl;
        return;
    }
    nlohmann::json config = nlohmann::json::parse(file);
    if(config.contains("resolution"))
    {
        auto resolution = config["resolution"];
        SCR_WIDTH = resolution[0];
        SCR_HEIGHT = resolution[1];
    }
    if(config.contains("camera"))
    {
        auto camera = config["camera"];
        if(camera["type"] == "perspective")
        {
            CAM_TYPE = CameraType::PERSPECTIVE;
        }
        else if(camera["type"] == "orthographic")
        {
            CAM_TYPE = CameraType::ORTHOGRAPHIC;
        }
        if(camera.contains("fx"))fx = camera["fx"];
        if(camera.contains("fy"))fy = camera["fy"];
        if(camera.contains("cx"))cx = camera["cx"];
        if(camera.contains("cy"))cy = camera["cy"];
    }
//    if(config.contains("object"))
//    {
//        auto object = config["object"];
//        for(int i = 0; i < object.size(); ++ i)
//        {
//            auto obj = object[i];
//
//        }
//    }
}

int main()
{
    loadJSON("../assets/config.json");
    std::shared_ptr<Viewer> mviewer;
    if(!fx || !fy || !cx || !cy) mviewer = std::make_shared<Viewer>(SCR_WIDTH, SCR_HEIGHT, CAM_TYPE, Shadertype::PHONG, "Cube Renderer");
    else mviewer = std::make_shared<Viewer>(SCR_WIDTH, SCR_HEIGHT, CAM_TYPE, Shadertype::PHONG, "Cube Renderer", fx, fy, cx, cy);
    auto mscene = mviewer->getScene();
    auto mloader = std::make_shared<Loader>();
    const std::string path = "../assets/cube.obj";
    auto mobject = mloader->load(path);
    mobject->setColor(glm::vec3{1.0f, 1.0f, 1.0f});
    mobject->setModelMatrix(glm::vec3{0.0f, 0.0f, 0.0f});
    mobject->setMaterial(glm::vec3 {1.0, 0.5f, 0.31f}, glm::vec3 {1.0f, 0.5f, 0.31f}, glm::vec3 {0.5f, 0.5f, 0.5f});
    mobject->setup();
    mscene->addObject(mobject);

    // Render loop
    mviewer->mainloop();
    return 0;
}