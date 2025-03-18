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

    // Movement controls
    void moveForward(float deltaTime);
    void moveBackward(float deltaTime);
    void moveLeft(float deltaTime);
    void moveRight(float deltaTime);
    void moveUp(float deltaTime);
    void moveDown(float deltaTime);

    // Mouse rotation control
    void processMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);

    // Setters for movement parameters
    void setMovementSpeed(float speed) { mMovementSpeed = speed; }
    void setMouseSensitivity(float sensitivity) { mMouseSensitivity = sensitivity; }


protected:
    glm::Matrix4 mViewMatrix{1.0f};
    glm::vec3 mPosition{0.0f};
    glm::vec3 mFront{0.0f, 0.0f, -1.0f};
    glm::vec3 mUp{0.0f, 1.0f, 0.0f};
    glm::vec3 mRight{1.0f, 0.0f, 0.0f};

    float mYaw = -90.0f;
    float mPitch = 0.0f;
    float mMovementSpeed = 2.5f;
    float mMouseSensitivity = 0.1f;

    void updateCameraVectors();
};


#endif //TOY_RENDERER_CAMERA_H
