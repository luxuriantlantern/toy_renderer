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
        case Shadertype::PHONG:
            setupPhongShader();
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

void Renderer::setupPhongShader() {
    const char *vertexShaderSource = "#version 330 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "layout (location = 1) in vec3 aNormal;\n"
                                     "out vec3 FragPos;\n"
                                     "out vec3 Normal;\n"
                                     "uniform mat4 model;\n"
                                     "uniform mat4 view;\n"
                                     "uniform mat4 projection;\n"
                                     "void main()\n"
                                     "{\n"
                                     "    FragPos = vec3(model * vec4(aPos, 1.0));\n"
                                     "    Normal = mat3(transpose(inverse(model))) * aNormal;\n"
                                     "    gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
                                     "}\n";

    const char *fragmentShaderSource = "#version 330 core\n"
                                       "out vec4 FragColor;\n"
                                       "in vec3 FragPos;\n"
                                       "in vec3 Normal;\n"
                                       "uniform vec3 objectColor;\n"
                                       "uniform vec3 lightColor;\n"
                                       "uniform vec3 lightPos;\n"
                                       "uniform vec3 viewPos;\n"
                                       "void main()\n"
                                       "{\n"
                                       "    // Ambient\n"
                                       "    float ambientStrength = 0.1;\n"
                                       "    vec3 ambient = ambientStrength * lightColor;\n"
                                       "    \n"
                                       "    // Diffuse\n"
                                       "    vec3 norm = normalize(Normal);\n"
                                       "    vec3 lightDir = normalize(lightPos - FragPos);\n"
                                       "    float diff = max(dot(norm, lightDir), 0.0);\n"
                                       "    vec3 diffuse = diff * lightColor;\n"
                                       "    \n"
                                       "    // Specular\n"
                                       "    float specularStrength = 0.5;\n"
                                       "    vec3 viewDir = normalize(viewPos - FragPos);\n"
                                       "    vec3 reflectDir = reflect(-lightDir, norm);\n"
                                       "    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);\n"
                                       "    vec3 specular = specularStrength * spec * lightColor;\n"
                                       "    \n"
                                       "    // Combine\n"
                                       "    vec3 result = (ambient + diffuse + specular) * objectColor;\n"
                                       "    FragColor = vec4(result, 1.0);\n"
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

    // Set light position at (1,1,1)
    glUseProgram(mShaderProgram);
    unsigned int lightPosLoc = glGetUniformLocation(mShaderProgram, "lightPos");
    glUniform3f(lightPosLoc, 1.0f, 1.0f, 1.0f);

    // Set default light color (white)
    unsigned int lightColorLoc = glGetUniformLocation(mShaderProgram, "lightColor");
    glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f);
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

    if (mShaderMode == Shadertype::PHONG) {
        unsigned int viewPosLoc = glGetUniformLocation(mShaderProgram, "viewPos");
        glUniform3fv(viewPosLoc, 1, glm::value_ptr(camera->getPosition()));
    }

    // Draw object
    glBindVertexArray(object->getVAO());
    glDrawElements(GL_TRIANGLES, object->getIndices().size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}