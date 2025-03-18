cmake_minimum_required(VERSION 3.10)
project(toy_renderer)

add_subdirectory(third_party)
add_executable(${PROJECT_NAME}
    main.cpp
    src/camera/camera.cpp
    src/ui/ui_manager.cpp
)


target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/third_party/imgui
        ${CMAKE_SOURCE_DIR}/third_party/imgui/backends
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        glfw
        glm
        imgui
)