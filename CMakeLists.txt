cmake_minimum_required(VERSION 3.10)
project(toy_renderer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(third_party)

add_executable(${PROJECT_NAME}
        main.cpp
        src/camera/camera.cpp
        src/ui/ui_manager.cpp
        src/scene/scene.cpp
        src/scene/object.cpp
        src/scene/cube.cpp
        src/render/render.cpp
        src/io/viewer.cpp
        src/io/loader.cpp
)
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/third_party/glad/include  # Add GLAD include first
        ${CMAKE_SOURCE_DIR}/third_party/imgui
        ${CMAKE_SOURCE_DIR}/third_party/imgui/backends
        ${CMAKE_SOURCE_DIR}/third_party/glfw/include  # Add GLFW include
        ${CMAKE_SOURCE_DIR}/third_party/glm          # Add GLM include
        ${CMAKE_SOURCE_DIR}/third_party/json/include
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        OpenGL::GL
        glad
        glfw
        glm
        imgui
        json
        imguifiledialog
)