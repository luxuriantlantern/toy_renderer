//
// Created by clx on 25-3-19.
//

#include "render.h"

Renderer::Renderer() {
    mShaderMode = Shadertype::DEFAULT;
    setupDefaultShader();
}

Renderer::Renderer(Shadertype mode)
{
    // TODO: Update renderer to support different shader modes
    mShaderMode = mode;
    switch (mode)
    {
        case Shadertype::DEFAULT:
            setupDefaultShader();
            break;
        default:
            setupDefaultShader();
    }
}

Renderer::~Renderer() {
    glDeleteProgram(mShaderProgram);
}

void Renderer::setupDefaultShader() {
    const char *vertexShaderSource = "#version 330 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "uniform mat4 model;\n"
                                     "uniform mat4 view;\n"
                                     "uniform mat4 projection;\n"
                                     "void main()\n"
                                     "{\n"
                                     "    gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
                                     "}\n";
    const char *fragmentShaderSource = "#version 330 core\n"
                                       "out vec4 FragColor;\n"
                                       "uniform vec3 objectColor;\n"
                                       "void main()\n"
                                       "{\n"
                                       "    FragColor = vec4(objectColor, 1.0);\n"
                                       "}\n";
    // Create shaders
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Create program and link shaders
    mShaderProgram = glCreateProgram();
    glAttachShader(mShaderProgram, vertexShader);
    glAttachShader(mShaderProgram, fragmentShader);
    glLinkProgram(mShaderProgram);

    // Clean up shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Renderer::renderObject(const Camera *camera, const Object *object)
{
    if(!camera || !object)return;

    glUseProgram(mShaderProgram);

    // Set up matrices
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = camera->getViewMatrix();
    glm::mat4 projection = camera->getProjectionMatrix();

    // Set up uniforms
    unsigned int modelLoc = glGetUniformLocation(mShaderProgram, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    unsigned int viewLoc = glGetUniformLocation(mShaderProgram, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    unsigned int projectionLoc = glGetUniformLocation(mShaderProgram, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    // Set up object color
    unsigned int objectColorLoc = glGetUniformLocation(mShaderProgram, "objectColor");
    glUniform3f(objectColorLoc, 1.0f, 1.0f, 1.0f);

    // Draw object
    glBindVertexArray(object->getVAO());
    glDrawElements(GL_TRIANGLES, object->getIndices().size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}