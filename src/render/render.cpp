//
// Created by clx on 25-3-19.
//

#include "render.h"

Renderer::Renderer() {
    if(mShaderProgram)glDeleteProgram(mShaderProgram), mShaderProgram = 0;
    mShaderMode = Shadertype::DEFAULT;
    setupDefaultShader();
}

Renderer::Renderer(Shadertype mode)
{
    if(mShaderProgram)glDeleteProgram(mShaderProgram), mShaderProgram = 0;
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
    mShaderProgram = 0;
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
                                       "struct Material {\n"
                                        "    vec3 ambient;\n"
                                        "    vec3 diffuse;\n"
                                        "    vec3 specular;\n"
                                        "    float shininess;\n"
                                        "};\n"
                                        "uniform Material material;\n"
                                       "void main()\n"
                                       "{\n"
                                       "    // Ambient\n"
                                       "    vec3 ambient = material.ambient * lightColor;\n"
                                       "    \n"
                                       "    // Diffuse\n"
                                       "    vec3 norm = normalize(Normal);\n"
                                       "    vec3 lightDir = normalize(lightPos - FragPos);\n"
                                       "    float diff = max(dot(norm, lightDir), 0.0);\n"
                                       "    vec3 diffuse = (diff * material.diffuse) * lightColor;\n"
                                       "    \n"
                                       "    // Specular\n"
                                       "    vec3 viewDir = normalize(viewPos - FragPos);\n"
                                       "    vec3 reflectDir = reflect(-lightDir, norm);\n"
                                       "    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);\n"
                                       "    vec3 specular = material.specular * spec * lightColor;\n"
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
    glUniform3f(lightPosLoc, lightpos.x, lightpos.y, lightpos.z);

    // Set default light color (white)
    unsigned int lightColorLoc = glGetUniformLocation(mShaderProgram, "lightColor");
    glUniform3f(lightColorLoc, lightcolor.r, lightcolor.g, lightcolor.b);
}

bool Renderer::setShaderType(Shadertype newType) {
    if(newType == mShaderMode)return true;
    if(mShaderProgram)
    {
        glDeleteProgram(mShaderProgram);
        mShaderProgram = 0;
    }
    mShaderMode = newType;
    switch (newType)
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
    return mShaderProgram != 0;
}

void Renderer::renderObject(const Camera *camera, const Object *object)
{
    if(!camera || !object)return;
    // Set material properties
    if (mShaderMode == Shadertype::PHONG) {
        unsigned int materialAmbientLoc = glGetUniformLocation(mShaderProgram, "material.ambient");
        glUniform3f(materialAmbientLoc, object->ambient.r, object->ambient.g, object->ambient.b);
        unsigned int materialDiffuseLoc = glGetUniformLocation(mShaderProgram, "material.diffuse");
        glUniform3f(materialDiffuseLoc, object->diffuse.r, object->diffuse.g, object->diffuse.b);
        unsigned int materialSpecularLoc = glGetUniformLocation(mShaderProgram, "material.specular");
        glUniform3f(materialSpecularLoc, object->specular.r, object->specular.g, object->specular.b);
    }

    glUseProgram(mShaderProgram);

    // Set up matrices
    glm::mat4 model = object->getModelMatrix();
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
    glUniform3f(objectColorLoc, object->getColor().r, object->getColor().g, object->getColor().b);

    if (mShaderMode == Shadertype::PHONG) {
        unsigned int viewPosLoc = glGetUniformLocation(mShaderProgram, "viewPos");
        glUniform3fv(viewPosLoc, 1, glm::value_ptr(camera->getPosition()));
    }

    // Draw object
    glBindVertexArray(object->getVAO());
    glDrawElements(GL_TRIANGLES, object->getIndices().size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Renderer::renderLight()
{
    if (mShaderMode != Shadertype::PHONG) return;

    // Create small cube geometry for light visualization
    static unsigned int lightVAO = 0;
    static unsigned int lightVBO = 0;
    static unsigned int lightEBO = 0;

    if (lightVAO == 0) {
        // Define cube vertices (size 0.05f)
        float size = 0.025f;  // Half-length of cube sides
        float vertices[] = {
                // Positions
                -size, -size, -size,  // 0
                size, -size, -size,  // 1
                size,  size, -size,  // 2
                -size,  size, -size,  // 3
                -size, -size,  size,  // 4
                size, -size,  size,  // 5
                size,  size,  size,  // 6
                -size,  size,  size   // 7
        };

        // Define indices for cube faces
        unsigned int indices[] = {
                0, 1, 2, 2, 3, 0,  // front
                1, 5, 6, 6, 2, 1,  // right
                5, 4, 7, 7, 6, 5,  // back
                4, 0, 3, 3, 7, 4,  // left
                3, 2, 6, 6, 7, 3,  // top
                4, 5, 1, 1, 0, 4   // bottom
        };

        // Create and bind VAO, VBO, EBO
        glGenVertexArrays(1, &lightVAO);
        glGenBuffers(1, &lightVBO);
        glGenBuffers(1, &lightEBO);

        glBindVertexArray(lightVAO);

        // Position attribute
        glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // Index buffer
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lightEBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // Configure vertex attributes
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindVertexArray(0);
    }

    // Use default shader for light object
    unsigned int currentProgram = mShaderProgram;
    setupDefaultShader();
    unsigned int lightProgram = mShaderProgram;

    glUseProgram(lightProgram);

    // Create transformation matrices
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, lightpos);

    // Get view and projection matrices from the most recently rendered object
    glm::mat4 view, projection;
    glGetUniformfv(currentProgram, glGetUniformLocation(currentProgram, "view"), glm::value_ptr(view));
    glGetUniformfv(currentProgram, glGetUniformLocation(currentProgram, "projection"), glm::value_ptr(projection));

    // Set uniforms
    unsigned int modelLoc = glGetUniformLocation(lightProgram, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    unsigned int viewLoc = glGetUniformLocation(lightProgram, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    unsigned int projectionLoc = glGetUniformLocation(lightProgram, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    // Set light color to white
    unsigned int objectColorLoc = glGetUniformLocation(lightProgram, "objectColor");
    glUniform3f(objectColorLoc, 1.0f, 1.0f, 1.0f);

    // Draw light cube
    glBindVertexArray(lightVAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // Switch back to Phong shader
    mShaderProgram = currentProgram;
    glUseProgram(currentProgram);
}