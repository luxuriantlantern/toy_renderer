//
// Created by clx on 25-3-19.
//

#ifndef OBJECT_H
#define OBJECT_H

#include <glad/glad.h>
#include <vector>
#include <glm/glm.hpp>


class Object {
public:
    Object() = default;
    ~Object();

    virtual void setup();
    virtual void cleanup();

    std::vector<glm::vec3> getVertices() const { return vertices; }
    std::vector<unsigned int> getIndices() const { return indices; }
    unsigned int getVAO() const{ return VAO; }

    void calculateNormals();

protected:
    std::vector<glm::vec3> vertices;
    std::vector<unsigned int> indices;
    std::vector<glm::vec3> normals;

    unsigned int VAO, VBO, EBO, NBO;
};

#endif //OBJECT_H
