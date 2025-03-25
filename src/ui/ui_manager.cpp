//
// Created by clx on 25-3-18.
//

#include "ui_manager.h"

void UI_Manager::init() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io.FontGlobalScale = 3.0f;
    ImGui_ImplGlfw_InitForOpenGL(mWindow, true);
    ImGui_ImplOpenGL3_Init();
}

void UI_Manager::startloop() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    int width, height;
    glfwGetFramebufferSize(mWindow, &width, &height);

    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(width / 2, height / 2));

    ImGui::Begin("Manual Bar", nullptr, ImGuiWindowFlags_MenuBar);
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("Camera parameter"))
        {
            if(mcamera->getType() == CameraType::PERSPECTIVE) {
                ImGui::Text("Camera Type: Perspective");

            }
            else {
                ImGui::Text("Camera Type: Orthographic");
            }
            glm::vec3 position = mcamera->getPosition();

            float pos[3] = { position.x, position.y, position.z };

            if (ImGui::InputFloat3("Position", pos)) {
                mcamera->setPosition(glm::vec3(pos[0], pos[1], pos[2]));
            }
            ImGui::Text("Camera Position Controls:");
            if (ImGui::InputFloat("X Position", &pos[0])) {
                position.x = pos[0];
                mcamera->setPosition(position);
            }
            if (ImGui::InputFloat("Y Position", &pos[1])) {
                position.y = pos[1];
                mcamera->setPosition(position);
            }
            if (ImGui::InputFloat("Z Position", &pos[2])) {
                position.z = pos[2];
                mcamera->setPosition(position);
            }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }
    ImGui::End();
}

void UI_Manager::endloop()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UI_Manager::cleanup() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}