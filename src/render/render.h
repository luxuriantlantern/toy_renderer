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

enum ShaderMode
{
    DEFAULT = 0,
    PHONG = 1,
    RAYTRACING = 2
};

class Renderer {
public:
    Renderer();
    Renderer(ShaderMode mode);

    ~Renderer();

    void renderObject(const Camera* camera, const Object* object);

private:
    unsigned int mShaderProgram;
    ShaderMode mShaderMode;
    void setupDefaultShader(); // Basic shader setup
};


#endif //TOY_RENDERER_RENDER_H
