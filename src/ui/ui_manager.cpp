//
// Created by clx on 25-3-18.
//

#include "ui_manager.h"
#include "ImGuiFileDialog.h"

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

    ImGui::SetNextWindowPos(ImVec2(width - 140, 10));
    ImGui::SetNextWindowSize(ImVec2(130, 70));
    ImGui::Begin("ShaderSelect", nullptr,
                 ImGuiWindowFlags_NoTitleBar |
                 ImGuiWindowFlags_NoResize |
                 ImGuiWindowFlags_NoMove |
                 ImGuiWindowFlags_NoScrollbar);

    if (ImGui::Button("D", ImVec2(50, 50))) {
        // Set Default shader
        mRenderer->setShaderType(Shadertype::DEFAULT);
    }
    ImGui::SameLine();
    if (ImGui::Button("P", ImVec2(50, 50))) {
        // Set Phong shader
        mRenderer->setShaderType(Shadertype::PHONG);
    }
    ImGui::End();

    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(width / 3, height * 2 / 3));

    ImGui::Begin("Manual Bar", nullptr, ImGuiWindowFlags_MenuBar);
    if (ImGui::BeginMenuBar())
    {
        // Add menu now comes first
        if(ImGui::BeginMenu("Add"))
        {
            if (ImGui::MenuItem("Open File"))
            {
                // Use correct parameters for OpenDialog
                ImGuiFileDialog::Instance()->OpenDialog(
                        "ChooseFileDlg",
                        "Choose File",
                        "3D Models{.obj,.ply},JSON{.json}"
                );
            }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    // Camera parameters shown directly in the window
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
    ImGui::End();
    glfwGetFramebufferSize(mWindow, &width, &height);

// Set dialog size to 80% of window size
    ImVec2 dialogSize = ImVec2(width * 0.8f, height * 0.8f);
    if (ImGuiFileDialog::Instance()->Display("ChooseFileDlg", ImGuiWindowFlags_NoCollapse, dialogSize))
    {
        if (ImGuiFileDialog::Instance()->IsOk())
        {
            std::string filePath = ImGuiFileDialog::Instance()->GetFilePathName();

            // Load the selected object
            try {
                std::shared_ptr<Object> object = mLoader->load(filePath);
                if (object) {
                    object->setColor(glm::vec3{1.0f, 1.0f, 1.0f});
                    object->setModelMatrix(glm::vec3{0.0f, 0.0f, 0.0f});
                    object->setMaterial(glm::vec3 {1.0, 0.5f, 0.31f}, glm::vec3 {1.0f, 0.5f, 0.31f}, glm::vec3 {0.5f, 0.5f, 0.5f});
                    object->setup();
                    mScene->addObject(object);
                    std::cout << "Loaded object from: " << filePath << std::endl;
                }
            }
            catch (const std::exception& e) {
                std::cerr << "Error loading object: " << e.what() << std::endl;
            }
        }

        // Close the dialog
        ImGuiFileDialog::Instance()->Close();
    }
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