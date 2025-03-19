//
// Created by clx on 25-3-19.
//

#include "object.h"

void Object::setup(){
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr >(vertices.size() * sizeof(glm::vec3)), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(indices.size() * sizeof(unsigned int)), &indices[0], GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Object::~Object(){
    if(VAO != 0){
        glDeleteVertexArrays(1, &VAO);
    }
    if(VBO != 0){
        glDeleteBuffers(1, &VBO);
    }
    if(EBO != 0) {
        glDeleteBuffers(1, &EBO);
    }
}

void Object::cleanup() {
    if(VAO != 0){
        glDeleteVertexArrays(1, &VAO);
    }
    if(VBO != 0){
        glDeleteBuffers(1, &VBO);
    }
    if(EBO != 0) {
        glDeleteBuffers(1, &EBO);
    }
}
