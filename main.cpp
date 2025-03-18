//
// Created by clx on 25-3-18.
//

#include <GLFW/glfw3.h>
#include "ui/ui_manager.h"
#include "camera/camera.h"

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
        glClear(GL_COLOR_BUFFER_BIT);

        float centerX = 800.0f / 2.0f;
        float centerY = 600.0f / 2.0f;
        float halfWidth = 200.0f;
        float halfHeight = 150.0f;

        glBegin(GL_QUADS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f((centerX - halfWidth) / 400.0f - 1.0f, (centerY - halfHeight) / 300.0f - 1.0f);
        glVertex2f((centerX + halfWidth) / 400.0f - 1.0f, (centerY - halfHeight) / 300.0f - 1.0f);
        glVertex2f((centerX + halfWidth) / 400.0f - 1.0f, (centerY + halfHeight) / 300.0f - 1.0f);
        glVertex2f((centerX - halfWidth) / 400.0f - 1.0f, (centerY + halfHeight) / 300.0f - 1.0f);
        glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ui_manager.cleanup();
    glfwTerminate();
    return 0;
}