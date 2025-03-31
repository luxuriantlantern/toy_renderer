//
// Created by clx on 25-3-18.
//

#ifndef TOY_RENDERER_UI_MANAGER_H
#define TOY_RENDERER_UI_MANAGER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../camera/camera.h"
#include <memory>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include "../scene/scene.h"
#include "../io/loader.h"

class UI_Manager {
public:
    UI_Manager(GLFWwindow *window,
               std::shared_ptr<Camera> camera,
               std::shared_ptr<Scene> scene,
               std::shared_ptr<Loader> loader)
                        : mWindow(window), mcamera(camera),
                          mLoader(loader), mScene(scene){this->init();}
    ~UI_Manager() = default;

    void init();
    void startloop();
    void endloop();
    void cleanup();

private:
    GLFWwindow *mWindow;
    std::shared_ptr<Camera> mcamera;
    std::shared_ptr<Scene> mScene;
    std::shared_ptr<Loader> mLoader;
};


#endif //TOY_RENDERER_UI_MANAGER_H
