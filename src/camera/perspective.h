//
// Created by clx on 25-3-17.
//

#ifndef TOY_RENDERER_PERSPECTIVE_H
#define TOY_RENDERER_PERSPECTIVE_H

#include "camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

const float pi = 3.1415927;

class PerspectiveCamera : public Camera{
public:
    PerspectiveCamera(float fov = 45.0f / 180.0f * pi,
                      float aspectRatio = 1.0f,
                      float near = 0.1f,
                      float far = 100.0f):
                      mfov(fov), maspectRatio(aspectRatio), mnear(near), mfar(far) {}

    void update() override {
        mViewMatrix = glm::lookAt(mPosition, mPosition + mFront, mUp);
        mProjectionMatrix = glm::perspective(mfov, aspectRatio, near, far);
    }

    CameraType getType() override {return PERSPECTIVE;}
private:
    float mfov;
    float maspectRatio;
    float mnear;
    float mfar;
};


#endif //TOY_RENDERER_PERSPECTIVE_H
