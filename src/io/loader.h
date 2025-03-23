//
// Created by ftc on 25-3-23.
//

#ifndef TOY_RENDERER_LOADER_H
#define TOY_RENDERER_LOADER_H

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <glm/glm.hpp>
#include <memory>
#include "../scene/object.h"

class Loader {
public:
    Loader() = default;
    ~Loader() = default;

    std::shared_ptr<Object> loadOBJ(const std::string& filePath);

private:
    void processVertex(const std::string& line, std::shared_ptr<Object> &mObject);
    void processNormal(const std::string& line, std::shared_ptr<Object> &mObject);
    void processFace(const std::string& line, std::shared_ptr<Object> &mObject);
    void processTexture(const std::string& line, std::shared_ptr<Object> &mObject);
};


#endif //TOY_RENDERER_LOADER_H
