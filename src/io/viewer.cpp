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

    muimanager = std::make_shared<UI_Manager>(mwindow);
}

void Viewer::mainloop()
{
    while (!glfwWindowShouldClose(mwindow)) {
        // Process input
        muimanager->startloop();
        processInput(mwindow);

        // Render
        mscene->render();
        mrenderer->renderLight();

        muimanager->endloop();
        // Swap buffers and poll events
        glfwSwapBuffers(mwindow);
        glfwPollEvents();
    }
    muimanager->cleanup();
}

Viewer::~Viewer() {
    glfwTerminate();
}

void Viewer::processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    float currentFrame = glfwGetTime();
    float deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // WASD movement (up, left, down, right) and JK movement (forward, backward)
    if (glfwGetKey(window, GLFW_KEY_W) || glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        mcamera->moveUp(deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        mcamera->moveDown(deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        mcamera->moveLeft(deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        mcamera->moveRight(deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
        mcamera->moveForward(deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
        mcamera->moveBackward(deltaTime);
    }

    // Mouse movement
    static bool firstMouse = true;
    static float lastX = 0.0f, lastY = 0.0f;
    static bool rightMousePressed = false;
    static bool leftMousePressed = false;

    int rightMouseState = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
    int leftMouseState = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);

    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    if (rightMouseState == GLFW_PRESS) {
        if (!rightMousePressed) {
            rightMousePressed = true;
            firstMouse = true;
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }

        if (firstMouse) {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos;

        lastX = xpos;
        lastY = ypos;

        mcamera->processRightMouseMovement(xoffset, yoffset);
    }
    else if (rightMousePressed) {
        rightMousePressed = false;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    if (leftMouseState == GLFW_PRESS) {
        if (!leftMousePressed) {
            leftMousePressed = true;
            firstMouse = true;
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }

        if (firstMouse) {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos;

        lastX = xpos;
        lastY = ypos;

        mcamera->processLeftMouseMovement(xoffset, yoffset);
    }
    else if (leftMousePressed) {
        leftMousePressed = false;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}