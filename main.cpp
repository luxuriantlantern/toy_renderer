//
// Created by clx on 25-3-18.
//

#include "ui/ui_manager.h"
#include "camera/camera.h"
#include <GLFW/glfw3.h>

int main()
{
    if (!glfwInit())
        return -1;

    GLFWwindow* window = glfwCreateWindow(800, 600, "Toy Renderer", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    UI_Manager ui_manager(window);
    ui_manager.init();

    while (!glfwWindowShouldClose(window)) {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ui_manager.cleanup();
    glfwTerminate();
    return 0;
}