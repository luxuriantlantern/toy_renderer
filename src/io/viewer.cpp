//
// Created by clx on 25-3-20.
//

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include "viewer.h"
#include "../io/loader.h"

//std::vector<std::shared_ptr<Object>> Viewer::loadJSON(const char* path, int &width, int &height, CameraType &cameratype, int &fx, int &fy, int &cx, int &cy)
//{
//    std::ifstream file(path);
//    std::vector<std::shared_ptr<Object>> objects;
//    objects.clear();
//    if(!file.is_open())
//    {
//        std::cerr << "Failed to open file: " << path << std::endl;
//        return objects;
//    }
//    nlohmann::json config = nlohmann::json::parse(file);
//    if(config.contains("resolution"))
//    {
//        auto resolution = config["resolution"];
//        width = resolution[0];
//        height = resolution[1];
//    }
//    if(config.contains("camera"))
//    {
//        auto camera = config["camera"];
//        cameratype = CameraType::PERSPECTIVE;
//        if(camera.contains("type"))
//        {
//            if(camera["type"] == "orthographic")
//            {
//                cameratype = CameraType::ORTHOGRAPHIC;
//            }
//        }
//        if(camera.contains("fx"))fx = camera["fx"];
//        if(camera.contains("fy"))fy = camera["fy"];
//        if(camera.contains("cx"))cx = camera["cx"];
//        if(camera.contains("cy"))cy = camera["cy"];
//    }
//    if(config.contains("objects"))
//    {
//        auto object = config["objects"];
//        auto loader = std::make_shared<Loader>();
//        for(int i = 0; i < object.size(); ++ i)
//        {
//            auto obj = object[i];
//            if(obj.contains("file"))
//            {
//                std::string pth = obj["file"];
//                auto mobject = loader->load(pth);
//                mobject->setColor(glm::vec3{1.0f, 1.0f, 1.0f});
//                mobject->setModelMatrix(glm::vec3{0.0f, 0.0f, 0.0f});
//                mobject->setMaterial(glm::vec3 {1.0, 0.5f, 0.31f}, glm::vec3 {1.0f, 0.5f, 0.31f}, glm::vec3 {0.5f, 0.5f, 0.5f});
//                if(obj.contains("position"))
//                {
//                    glm::vec3 pos = glm::vec3{obj["position"][0], obj["position"][1], obj["position"][2]};
//                    mobject->setModelMatrix(pos);
//                }
//                if(obj.contains("scale"))
//                {
//                    glm::vec3 scale = glm::vec3 {obj["scale"][0], obj["scale"][1], obj["scale"][2]};
//                    mobject->scale(scale);
//                }
//                if(obj.contains("rotation"))
//                {
//                    if(obj["rotation"].contains("type"))
//                    {
//                        if(obj["rotation"]["type"] == "euler_xyz")
//                        {
//                            glm::vec3 rot = glm::vec3{obj["rotation"]["data"][0], obj["rotation"]["data"][1], obj["rotation"]["data"][2]};
//                            mobject->rotateEulerXYZ(rot.x, rot.y, rot.z);
//                        }
//                        if(obj["rotation"]["type"] == "quaternion")
//                        {
//                            glm::quat quaternion = glm::quat(obj["rotation"]["data"][0], obj["rotation"]["data"][1],
//                                                             obj["rotation"]["data"][2], obj["rotation"]["data"][3]);
//                            mobject->rotateQuaternion(quaternion);
//                        }
//                    }
//                }
//                objects.push_back(mobject);
//            }
//        }
//    }
//    return objects;
//}

void Viewer::init(int width, int height, CameraType cameratype, Shadertype shadertype, const char *title) {
    // Initialize GLFW
    int fx{0}, fy{0}, cx{0}, cy{0};
    std::vector<std::shared_ptr<Object>> objects;
//    if(path != "")objects = loadJSON(path, width, height, cameratype, fx, fy, cx, cy);
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
    int w, h;
    glfwGetWindowSize(window, &w, &h);
    mcamera->setWindowSize(w, h);
    mscene->setCamera(mcamera);

    // Create objects
    for(auto &object : objects)
    {
        object->setup();
        mscene->addObject(object);
    }
    // Create renderer
    mrenderer = std::make_shared<Renderer>(shadertype);
    mscene->setRenderer(mrenderer);

    muimanager = std::make_shared<UI_Manager>(mwindow, mcamera, mscene, mrenderer, mloader);
}

void Viewer::mainloop()
{
    while (!glfwWindowShouldClose(mwindow)) {
        // Process input
        muimanager->startloop();
        processInput(mwindow);

        // Render
        int w, h;
        glfwGetWindowSize(mwindow, &w, &h);
        mscene->render(w, h);
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