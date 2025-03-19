//
// Created by 18067 on 25-3-19.
//

#ifndef OBJECT_H
#define OBJECT_H

#include <glad/glad.h>
#include <vector>
#include <glm/glm.hpp>


class Object {
public:
    Object() = default;
    virtual ~Object();

    virtual void setup();
    virtual void cleanup();
    virtual void render() const;

protected:
    std::vector<glm::vec3> vertices;
    std::vector<unsigned int> indices;

    unsigned int VAO{0};
    unsigned int VBO{0};
    unsigned int EBO{0};
};

#endif //OBJECT_H
