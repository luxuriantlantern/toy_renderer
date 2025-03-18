//
// Created by clx on 25-3-17.
//

#ifndef TOY_RENDERER_ORTHOGRAPHIC_H
#define TOY_RENDERER_ORTHOGRAPHIC_H

#include "camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class OrthographicCamera : public Camera{
public:
    OrthographicCamera(float left = -1.0f,
                       float right = 1.0f,
                       float bottom = -1.0f,
                       float top = 1.0f,
                       float near = -1.0f,
                       float far = 1.0f):
            mleft(left), mright(right), mbottom(bottom), mtop(top), mnear(near), mfar(far) {}

    void update() override {
        mViewMatrix = glm::lookAt(mPosition, mPosition + mFront, mUp);
        mProjectionMatrix = glm::ortho(left, right, bottom, top, near, far);
    }

    CameraType getType() override {return ORTHOGRAPHIC;}

    void setOrthoSize(float left, float right, float bottom, float top) {
        mleft = left; mright = right;
        mbottom = bottom; mtop = top;
    }
    void setNearFar(float near, float far) { mnear = near; mfar = far; }

    glm::mat4 getProjectionMatrix() const { return mProjectionMatrix; }

protected:
    glm::mat4 mProjectionMatrix{1.0f};

private:
    float mleft;
    float mright;
    float mbottom;
    float mtop;
    float mnear;
    float mfar;
};

#endif //TOY_RENDERER_ORTHOGRAPHIC_H
