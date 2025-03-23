//
// Created by clx on 25-3-19.
//

#include "cube.h"

Cube::Cube() {
    vertices = {
            // Front face
            glm::vec3(-0.5f, -0.5f, 0.5f),  // bottom-left
            glm::vec3(0.5f, -0.5f, 0.5f),   // bottom-right
            glm::vec3(0.5f, 0.5f, 0.5f),    // top-right
            glm::vec3(-0.5f, 0.5f, 0.5f),   // top-left

            // Back face
            glm::vec3(-0.5f, -0.5f, -0.5f), // bottom-left
            glm::vec3(0.5f, -0.5f, -0.5f),  // bottom-right
            glm::vec3(0.5f, 0.5f, -0.5f),   // top-right
            glm::vec3(-0.5f, 0.5f, -0.5f)   // top-left
    };

    indices = {
            // Front face
            0, 1, 2,
            2, 3, 0,

            // Right face
            1, 5, 6,
            6, 2, 1,

            // Back face
            5, 4, 7,
            7, 6, 5,

            // Left face
            4, 0, 3,
            3, 7, 4,

            // Top face
            3, 2, 6,
            6, 7, 3,

            // Bottom face
            4, 5, 1,
            1, 0, 4
    };
}

void Cube::initialize() {
    Object::setup();
}