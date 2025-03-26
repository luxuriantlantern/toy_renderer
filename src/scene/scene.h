//
// Created by clx on 25-3-19.
//

#ifndef TOY_RENDERER_SCENE_H
#define TOY_RENDERER_SCENE_H

#include "../camera/camera.h"
#include "object.h"
#include "../render/render.h"
#include <memory>
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>

class Scene {
public:
    Scene();
    ~Scene() = default;

    void addObject(std::shared_ptr<Object> object);
    void setCamera(std::shared_ptr<Camera> camera);
    void setRenderer(std::shared_ptr<Renderer> renderer);
    void render(int w, int h);

    std::shared_ptr<Camera> getCamera() const { return mCamera; }

private:
    std::vector<std::shared_ptr<Object>> mObjects;
    std::shared_ptr<Camera> mCamera;
    std::shared_ptr<Renderer> mRenderer;
};

#endif //TOY_RENDERER_SCENE_H