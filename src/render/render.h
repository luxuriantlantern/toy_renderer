//
// Created by clx on 25-3-19.
//

#ifndef TOY_RENDERER_RENDER_H
#define TOY_RENDERER_RENDER_H


#include "../camera/camera.h"
#include "../scene/object.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

enum Shadertype
{
    DEFAULT = 0,
    PHONG = 1,
};

class Renderer {
public:
    Renderer();
    Renderer(Shadertype mode);

    ~Renderer();

    void renderObject(const Camera* camera, const Object* object);
    void renderLight();
    bool setShaderType(Shadertype mode);

private:
    unsigned int mShaderProgram = 0;
    Shadertype mShaderMode;
    void setupDefaultShader(); // Basic shader setup
    void setupPhongShader(); // Phong shader setup

    glm::vec3 lightpos{1.5f, 1.5f, 1.5f};
    glm::vec3 lightcolor{1.0f, 1.0f, 1.0f};
};


#endif //TOY_RENDERER_RENDER_H
