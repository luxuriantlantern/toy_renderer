//
// Created by ftc on 25-3-23.
//

#include "loader.h"
#include <iostream>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

std::shared_ptr<Object> Loader::loadOBJ(const std::string& filePath) {
    std::ifstream file(filePath);
    if(!file.is_open()) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return nullptr;
    }

    auto mObject = std::make_shared<Object>();
    std::string line;
    bool isinitialize = false;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;

        if (prefix == "v") {
            processVertex(line, mObject);
        } else if (prefix == "vn") {
            processNormal(line, mObject);
        } else if (prefix == "f") {
            if(!isinitialize)mObject->normals.resize(mObject->vertices.size(), glm::vec3(0.0f)), isinitialize=true;
            processFace(line, mObject);
        } else if (prefix == "vt") {
            processTexture(line, mObject);
        }
    }
    for(int i = 0; i < mObject->normals.size(); i++) {
        mObject->normals[i] = glm::normalize(mObject->normals[i]);
    }
    return mObject;
}

void Loader::processVertex(const std::string& line, std::shared_ptr<Object> &mObject) {
    std::istringstream iss(line);
    std::string prefix;
    iss >> prefix;
    glm::vec3 vertex;
    iss >> vertex.x >> vertex.y >> vertex.z;
    mObject->vertices.push_back(vertex);
}

void Loader::processNormal(const std::string& line, std::shared_ptr<Object> &mObject) {
    std::istringstream iss(line);
    std::string prefix;
    iss >> prefix;
    glm::vec3 normal;
    iss >> normal.x >> normal.y >> normal.z;
    mObject->facenormals.push_back(normal);
}

void Loader::processFace(const std::string& line, std::shared_ptr<Object> &mObject) {
    std::istringstream iss(line);
    std::string prefix;
    iss >> prefix;
    std::string vertex;
    while (iss >> vertex) {
        std::istringstream vss(vertex);
        std::string index;
        std::vector<int> indices;
        while (std::getline(vss, index, '/')) {
            indices.push_back(std::stoi(index));
        }
        mObject->indices.push_back(indices[0] - 1);
        mObject->normals[indices[0] - 1] += mObject->facenormals[indices[2] - 1];
    }
    mObject->indices.push_back(mObject->indices[mObject->indices.size() - 2]);
    mObject->indices.push_back(mObject->indices[mObject->indices.size() - 5]);

}

void Loader::processTexture(const std::string& line, std::shared_ptr<Object> &mObject) {
    std::istringstream iss(line);
    std::string prefix;
    iss >> prefix;
    glm::vec2 texCoord;
    iss >> texCoord.x >> texCoord.y;
    mObject->texCoords.push_back(texCoord);
}