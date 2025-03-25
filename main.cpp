//
// Created by clx on 25-3-18.
//

#include <memory>
#include "scene/cube.h"
#include "io/viewer.h"
#include "io/loader.h"

// Window dimensions
unsigned int SCR_WIDTH = 2560;
unsigned int SCR_HEIGHT = 2560;
CameraType CAM_TYPE = CameraType::PERSPECTIVE;

void loadJSON(const std::string &path)
{
    std::ifstream ifs(path);
    if (!ifs.is_open())
    {
        std::cerr << "Failed to open file: " << path << std::endl;
        return;
    }

    std::stringstream buffer;
    buffer << ifs.rdbuf();
    std::string content = buffer.str();

    size_t resPos = content.find("\"resolution\"");
    size_t openBracket = content.find('[', resPos);
    size_t comma = content.find(',', openBracket);
    size_t closeBracket = content.find(']', comma);

    SCR_WIDTH = std::stoi(content.substr(openBracket + 1, comma - openBracket - 1));
    SCR_HEIGHT = std::stoi(content.substr(comma + 1, closeBracket - comma - 1));

    size_t typePos = content.find("\"type\"", content.find("\"camera\""));
    size_t typeValueStart = content.find(':', typePos) + 1;
    size_t typeValueEnd = content.find(',', typeValueStart);
    std::string cameraTypeStr = content.substr(typeValueStart, typeValueEnd - typeValueStart);

    cameraTypeStr.erase(std::remove(cameraTypeStr.begin(), cameraTypeStr.end(), '\"'), cameraTypeStr.end());
    cameraTypeStr.erase(std::remove(cameraTypeStr.begin(), cameraTypeStr.end(), ' '), cameraTypeStr.end());
    cameraTypeStr.erase(std::remove(cameraTypeStr.begin(), cameraTypeStr.end(), '}'), cameraTypeStr.end());
    cameraTypeStr.erase(std::remove(cameraTypeStr.begin(), cameraTypeStr.end(), '\n'), cameraTypeStr.end());


    CAM_TYPE = (cameraTypeStr == "perspective") ?
                            CameraType::PERSPECTIVE : CameraType::ORTHOGRAPHIC;
}

int main()
{
    loadJSON("../assets/config.json");
    auto mviewer = std::make_shared<Viewer>(SCR_WIDTH, SCR_HEIGHT, CAM_TYPE, Shadertype::PHONG, "Cube Renderer");
    auto mscene = mviewer->getScene();
    auto mloader = std::make_shared<Loader>();
    const std::string path = "../assets/cube.obj";
    auto mobject = mloader->load(path);
    mobject->setColor(glm::vec3{1.0f, 1.0f, 1.0f});
    mobject->setModelMatrix(glm::vec3{0.0f, 0.0f, 0.0f});
    mobject->setMaterial(glm::vec3 {1.0, 0.5f, 0.31f}, glm::vec3 {1.0f, 0.5f, 0.31f}, glm::vec3 {0.5f, 0.5f, 0.5f});
    mobject->setup();
    mscene->addObject(mobject);

    // Render loop
    mviewer->mainloop();
    return 0;
}