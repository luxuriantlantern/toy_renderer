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
    static const int MAX_PLOT_POINTS = 100;
    float posX_history[MAX_PLOT_POINTS] = {0};
    float posY_history[MAX_PLOT_POINTS] = {0};
    float posZ_history[MAX_PLOT_POINTS] = {0};
    int values_offset = 0;
    bool plot_paused = false;
};


#endif //TOY_RENDERER_UI_MANAGER_H
