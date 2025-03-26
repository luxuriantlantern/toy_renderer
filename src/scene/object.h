//
// Created by clx on 25-3-19.
//

#ifndef OBJECT_H
#define OBJECT_H

#include <glad/glad.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>


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
    void scale(const glm::vec3 &scale) { model = glm::scale(model, scale); }
    void rotate(float angleInDegrees, const glm::vec3& axis) {
        model = glm::rotate(model, glm::radians(angleInDegrees), glm::normalize(axis));
    }
    void rotateEulerXYZ(float angleX, float angleY, float angleZ) {
        float radX = glm::radians(angleX);
        float radY = glm::radians(angleY);
        float radZ = glm::radians(angleZ);

        glm::mat4 rotX = glm::rotate(glm::mat4(1.0f), radX, glm::vec3(1.0f, 0.0f, 0.0f));
        glm::mat4 rotY = glm::rotate(glm::mat4(1.0f), radY, glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 rotZ = glm::rotate(glm::mat4(1.0f), radZ, glm::vec3(0.0f, 0.0f, 1.0f));

        model = model * rotZ * rotY * rotX;
    }

    void rotateQuaternion(const glm::quat& quaternion) {
        glm::mat4 rotationMatrix = glm::mat4_cast(quaternion);
        model = model * rotationMatrix;
    }
    void rotateQuaternion(float angleInDegrees, const glm::vec3& axis) {
        glm::quat quaternion = glm::angleAxis(glm::radians(angleInDegrees), glm::normalize(axis));
        rotateQuaternion(quaternion);
    }

    glm::vec3 ambient{0.2f, 0.2f, 0.2f}, diffuse{0.5f, 0.5f, 0.5f}, specular{1.0f, 1.0f, 1.0f};

    std::vector<glm::vec3> vertices;
    std::vector<unsigned int> indices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> texCoords;
    std::vector<glm::vec3> facenormals;
    bool normalcalculated = false;

protected:
    unsigned int VAO, VBO, EBO, NBO;

    glm::mat4 model{1.0f};
    glm::vec3 color{1.0f, 1.0f, 1.0f};
};

#endif //OBJECT_H
