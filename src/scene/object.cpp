//
// Created by clx on 25-3-19.
//

#include "object.h"

void Object::calculateNormals() {
    normals.resize(vertices.size(), glm::vec3(0.0f));

    for (unsigned int i = 0; i < indices.size(); i += 3) {
        glm::vec3 v1 = vertices[indices[i]];
        glm::vec3 v2 = vertices[indices[i + 1]];
        glm::vec3 v3 = vertices[indices[i + 2]];

        glm::vec3 normal = glm::normalize(glm::cross(v2 - v1, v3 - v1));

        normals[indices[i]] += normal;
        normals[indices[i + 1]] += normal;
        normals[indices[i + 2]] += normal;
    }

    for (unsigned int i = 0; i < normals.size(); i++) {
        normals[i] = glm::normalize(normals[i]);
    }
}

void Object::setup(){

    if(!normalcalculated)calculateNormals();

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenBuffers(1, &NBO);

    glBindVertexArray(VAO);

    // Position attribute
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr >(vertices.size() * sizeof(glm::vec3)), &vertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glEnableVertexAttribArray(0);

    // Normal attribute
    glBindBuffer(GL_ARRAY_BUFFER, NBO);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(normals.size() * sizeof(glm::vec3)), &normals[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(indices.size() * sizeof(unsigned int)), &indices[0], GL_STATIC_DRAW);

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
    if(NBO != 0) {
        glDeleteBuffers(1, &NBO);
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
    if(NBO != 0) {
        glDeleteBuffers(1, &NBO);
    }
}
