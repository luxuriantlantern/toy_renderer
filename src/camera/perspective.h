//
// Created by clx on 25-3-17.
//

#ifndef TOY_RENDERER_PERSPECTIVE_H
#define TOY_RENDERER_PERSPECTIVE_H

#include "camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class PerspectiveCamera : public Camera{
public:
    PerspectiveCamera(float fov = 45.0f,
                      float aspectRatio = 1.0f,
                      float near = 0.1f,
                      float far = 100.0f,
                      glm::vec3 position = glm::vec3(0.0f, 1.0f, 3.0f)):
                      Camera(position),
                      mfov(fov),
                      maspectRatio(aspectRatio),
                      mnear(near),
                      mfar(far) {}


    void update() override {
        mViewMatrix = glm::lookAt(mPosition, mPosition + mFront, mUp);
        mProjectionMatrix = glm::perspective(mfov, maspectRatio, mnear, mfar);
    }

    CameraType getType() override {return PERSPECTIVE;}

    void setFov(float fov) {mfov = fov;}
    void setAspectRatio(float aspectRatio) {maspectRatio = aspectRatio;}
    void setNear(float near) {mnear = near;}
    void setFar(float far) {mfar = far;}

    float getFov() const {return mfov;}
    float getAspectRatio() const {return maspectRatio;}
    float getNear() const {return mnear;}
    float getFar() const {return mfar;}

private:
    float mfov;
    float maspectRatio;
    float mnear;
    float mfar;
};


#endif //TOY_RENDERER_PERSPECTIVE_H
