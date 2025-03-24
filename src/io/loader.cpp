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
    mObject->normalcalculated = true;
    return mObject;
}

std::shared_ptr<Object> Loader::loadPLY(const std::string& filePath) {
    std::ifstream file(filePath);
    if(!file.is_open()) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return nullptr;
    }

    auto mObject = std::make_shared<Object>();
    std::string line;
    int numVertices, numFaces;
    while(std::getline(file, line)) {
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;
        if(prefix == "element") {
            std::string type;
            iss >> type;
            if(type == "vertex") {
                iss >> numVertices;
                mObject->vertices.reserve(numVertices);
                mObject->normals.resize(numVertices, glm::vec3(0.0f));
            } else if(type == "face") {
                iss >> numFaces;
                mObject->indices.reserve(numFaces * 3);
            }
        } else if(prefix == "end_header") {
            break;
        }
    }

    for(int i = 0; i < numVertices && std::getline(file, line); i++) {
        std::istringstream iss(line);
        glm::vec3 vertex;
        iss >> vertex.x >> vertex.y >> vertex.z;

        glm::vec3 normal(0.0f);
        if(iss >> normal.x >> normal.y >> normal.z) {
            mObject->normals[i] = normal;
        }

        mObject->vertices.push_back(vertex);
    }

    for(int i = 0; i < numFaces && std::getline(file, line); i++) {
        std::istringstream iss(line);
        int vertCount;
        iss >> vertCount;

        if (vertCount >= 3) {
            std::vector<int> faceIndices;
            for (int j = 0; j < vertCount; j++) {
                int idx;
                iss >> idx;
                faceIndices.push_back(idx);
            }

            for (int j = 1; j < vertCount - 1; j++) {
                mObject->indices.push_back(faceIndices[0]);
                mObject->indices.push_back(faceIndices[j]);
                mObject->indices.push_back(faceIndices[j + 1]);
            }
        }
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
    std::vector<int> Indices;
    while (iss >> vertex) {
        std::istringstream vss(vertex);
        std::string index;
        std::vector<int> indices;
        while (std::getline(vss, index, '/')) {
            indices.push_back(std::stoi(index));
        }
        Indices.push_back(indices[0] - 1);
        mObject->normals[indices[0] - 1] += mObject->facenormals[indices[2] - 1];
    }
    for(int i = 1; i < Indices.size() - 1; ++ i)
    {
        mObject->indices.push_back(Indices[0]);
        mObject->indices.push_back(Indices[i]);
        mObject->indices.push_back(Indices[i + 1]);
    }
}

void Loader::processTexture(const std::string& line, std::shared_ptr<Object> &mObject) {
    std::istringstream iss(line);
    std::string prefix;
    iss >> prefix;
    glm::vec2 texCoord;
    iss >> texCoord.x >> texCoord.y;
    mObject->texCoords.push_back(texCoord);
}