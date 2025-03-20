//
// Created by clx on 25-3-18.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <memory>
#include "scene/cube.h"
#include "ui/viewer.h"

// Window dimensions
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//int main()
//{
//    auto mviewer = std::make_shared<Viewer>(SCR_WIDTH, SCR_HEIGHT, CameraType::PERSPECTIVE, Shadertype::DEFAULT, "Cube Renderer");
//    auto mcube = std::make_shared<cube>();
//    mcube->initialize();
//    auto mscene = mviewer->getScene();
//    mscene->addObject(mcube);
//    // Render loop
//    mviewer->mainloop();
//
//    return 0;
//}

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main()
{
    auto mviewer = std::make_shared<Viewer>(SCR_WIDTH, SCR_HEIGHT, CameraType::PERSPECTIVE, Shadertype::DEFAULT, "Cube Renderer");
    auto mcube = std::make_shared<cube>();
    mcube->initialize();
    auto mscene = mviewer->getScene();
    mscene->addObject(mcube);
    // Render loop
    mviewer->mainloop();
    return 0;
}

// Process keyboard input
void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

}

// Adjust viewport on window resize
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}