# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(glfw)

# GLM
add_library(glm INTERFACE)
target_include_directories(glm INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/glm
)

# GLAD
add_library(glad STATIC
        glad/src/glad.c
)
target_include_directories(glad PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/glad/include
)
target_link_libraries(glad PUBLIC
        ${CMAKE_DL_LIBS}
)

# ImGui
add_library(imgui STATIC
    imgui/imgui.cpp
    imgui/imgui_demo.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
    imgui/backends/imgui_impl_glfw.cpp
    imgui/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends
    ${CMAKE_CURRENT_SOURCE_DIR}/glad/include
)

target_link_libraries(imgui PUBLIC
        glfw
        glad
)

# nlohmann/json
add_library(json INTERFACE)
target_include_directories(json INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/json/include
)

# ImGuiFileDialog
add_library(imguifiledialog STATIC
        ImGuiFileDialog/ImGuiFileDialog.cpp
)

target_include_directories(imguifiledialog PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/ImGuiFileDialog
)

target_link_libraries(imguifiledialog PUBLIC
        imgui
)