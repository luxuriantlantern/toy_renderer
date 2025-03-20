//
// Created by clx on 25-3-20.
//

#include <iostream>
#include "viewer.h"

void Viewer::init(int width, int height, CameraType cameratype, Shadertype shadertype, const char *title) {
    // Initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window
    GLFWwindow* window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    });

    // Load GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }

    this->mwindow = window;

    // Create scene
    mscene = std::make_shared<Scene>();

    // Create camera
    switch(cameratype) {
        case CameraType::PERSPECTIVE:
            mcamera = std::make_shared<PerspectiveCamera>();
            break;
        case CameraType::ORTHOGRAPHIC:
            mcamera = std::make_shared<OrthographicCamera>();
            break;
        default:
            mcamera = std::make_shared<PerspectiveCamera>();
    }
    mscene->setCamera(mcamera);

    // Create renderer
    mrenderer = std::make_shared<Renderer>(shadertype);
    mscene->setRenderer(mrenderer);
}

void Viewer::mainloop()
{
    while (!glfwWindowShouldClose(mwindow)) {
        // Process input
        processInput(mwindow);

        // Render
        mscene->render();

        // Swap buffers and poll events
        glfwSwapBuffers(mwindow);
        glfwPollEvents();
    }
}

Viewer::~Viewer() {
    glfwTerminate();
}

void Viewer::processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

//    float currentFrame = glfwGetTime();
//    float deltaTime = currentFrame - lastFrame;
//    lastFrame = currentFrame;
//
//    // WASD movement (left, right, forward, backward)
//    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
//        mcamera->moveUp(deltaTime);
//    }
//    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
//        mcamera->moveDown(deltaTime);
//    }
//    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
//        mcamera->moveLeft(deltaTime);
//    }
//    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
//        mcamera->moveRight(deltaTime);
//    }
//
//    // J and K for up and down movement
//    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
//        mcamera->moveForward(deltaTime);
//    }
//    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
//        mcamera->moveBackward(deltaTime);
//    }
}