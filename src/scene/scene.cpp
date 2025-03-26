//
// Created by clx on 25-3-19.
//

#include "scene.h"

Scene::Scene() {
    mCamera = nullptr;
}

void Scene::addObject(std::shared_ptr<Object> object) {
    mObjects.push_back(object);
}

void Scene::setCamera(std::shared_ptr<Camera> camera) {
    mCamera = camera;
}

void Scene::setRenderer(std::shared_ptr<Renderer> renderer) {
    mRenderer = renderer;
}

void Scene::render(int w, int h) {
    if (mCamera == nullptr) {
        return;
    }
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mCamera->update(w, h);

    for (auto &object : mObjects) {
        mRenderer->renderObject(mCamera.get(), object.get());
    }
}