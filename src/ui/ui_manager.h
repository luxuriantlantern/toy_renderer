//
// Created by clx on 25-3-18.
//

#ifndef TOY_RENDERER_UI_MANAGER_H
#define TOY_RENDERER_UI_MANAGER_H

#include <GLFW/glfw3.h>
#include "../camera/camera.h"
#include <memory>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

class UI_Manager {
public:
    UI_Manager(GLFWwindow *window, std::shared_ptr<Camera> camera)
                        : mWindow(window), mcamera(camera) {this->init();}
    ~UI_Manager() = default;

    void init();
    void startloop();
    void endloop();
    void cleanup();

private:
    GLFWwindow *mWindow;
    std::shared_ptr<Camera> mcamera;
};


#endif //TOY_RENDERER_UI_MANAGER_H
