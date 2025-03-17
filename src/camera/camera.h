//
// Created by ftc on 25-3-17.
//

#ifndef TOY_RENDERER_CAMERA_H
#define TOY_RENDERER_CAMERA_H

#include<glm/glm.hpp>

enum CameraType {
    PERSPECTIVE,
    ORTHOGRAPHIC
};

class Camera {
public:
    Camera() = default;
    virtual ~Camera() = default;
    Camera(const Camera &other) {*this = other;}
    Camera &operator=(const Camera &other) {*this = other; return *this;}

    virtual void update() = 0;
    glm::Matrix4 getViewMatrix() const {return mViewMatrix;}
    virtual CameraType getType() = 0;

protected:
    glm::Matrix4 mViewMatrix{1.0f};
    glm::vec3 mPosition{0.0f};
    glm::vec3 mFront{0.0f, 0.0f, -1.0f};
    glm::vec3 mUp{0.0f, 1.0f, 0.0f};
    glm::vec3 mRight{1.0f, 0.0f, 0.0f};
};


#endif //TOY_RENDERER_CAMERA_H
