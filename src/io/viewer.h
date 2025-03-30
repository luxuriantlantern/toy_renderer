//
// Created by clx on 25-3-20.
//

#ifndef VIEWER_H
#define VIEWER_H

#include "camera/orthographic.h"
#include "camera/perspective.h"
#include "scene/scene.h"
#include "GLFW/glfw3.h"
#include <memory>
#include "../ui/ui_manager.h"
#include "../io/loader.h"


class Viewer {
public:
    Viewer() = default;
    Viewer(int width, int height, CameraType cameratype, Shadertype type, const char* title) {
        init(width, height, cameratype, type, title);
    };
    ~Viewer();

    void init(int width, int height, CameraType cameratype, Shadertype type, const char* title);
    void mainloop();
    void processInput(GLFWwindow* window);
//    std::vector<std::shared_ptr<Object>>
//        loadJSON(const char* path, int &width, int &height, CameraType &cameratype, int &fx, int &fy, int &cx, int &cy);

    std::shared_ptr<Scene> getScene() { return mscene; }
    std::shared_ptr<Loader> getLoader() { return mloader; }

private:
    GLFWwindow* mwindow;
    std::shared_ptr<Scene> mscene;
    std::shared_ptr<Camera> mcamera;
    std::shared_ptr<Renderer> mrenderer;
    float lastFrame = 0.0f;
    std::shared_ptr<UI_Manager> muimanager;
    std::shared_ptr<Loader> mloader;
};



#endif //VIEWER_H
