//
// Created by clx on 25-3-19.
//

#ifndef OBJECT_H
#define OBJECT_H

#include <glad/glad.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Object {
public:
    Object() = default;
    ~Object();

    virtual void setup();
    virtual void cleanup();

    std::vector<glm::vec3> getVertices() const { return vertices; }
    std::vector<unsigned int> getIndices() const { return indices; }
    unsigned int getVAO() const{ return VAO; }
    glm::mat4 getModelMatrix() const { return model; }
    glm::vec3 getColor() const { return color; }

    void setModelMatrix(const glm::mat4 &modelMatrix) { model = modelMatrix; }
    void setModelMatrix(const glm::vec3 pos){ model = glm::translate(model, pos); }
    void setColor(const glm::vec3 &objectColor) { color = objectColor; }
    void calculateNormals();
    void setMaterial(const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular)
    {
        this->ambient = ambient;
        this->diffuse = diffuse;
        this->specular = specular;
    };

    glm::vec3 ambient{0.2f, 0.2f, 0.2f}, diffuse{0.5f, 0.5f, 0.5f}, specular{1.0f, 1.0f, 1.0f};

protected:
    std::vector<glm::vec3> vertices;
    std::vector<unsigned int> indices;
    std::vector<glm::vec3> normals;

    unsigned int VAO, VBO, EBO, NBO;

    glm::mat4 model{1.0f};
    glm::vec3 color{1.0f, 1.0f, 1.0f};
};

#endif //OBJECT_H
