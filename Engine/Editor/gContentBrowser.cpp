#include "gContentBrowser.h"

#include "Core/gCommon.h"
#include "ImGuiFileDialog.h"

#include <glm/gtc/type_ptr.hpp>

#include "Core/gObject.h"
#include <functional>
#include "ImGuiFileDialog.h"
#include <fstream>
#include <string>


static bool ShowObjectHierarchy = false;

 Scene& myScene = Scene::Instance();
 ObjectList& objectList = ObjectList::getInstance();

void ContentBrowser::DrawBrowser()
{

    ImVec2 buttonSize = ImVec2(60, 30);

    int w, h;
    WindowScale(window, &w, &h);

    //int panelHeight = std::max(h - 2500, 150);

    DrawPanel("Browser", ImVec2(0, 150), ImVec2(w / 7, h/ 2), [&]()
        {


            int columnCount = 0;
            static bool showFileDialog = false;

            Mesh* meshInstance = nullptr;



            if (ImGui::Button("Import", buttonSize)) {
                ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".obj,.fbx", ".");
                showFileDialog = true;
            }

            if (showFileDialog) {
                if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey")) {
                    if (ImGuiFileDialog::Instance()->IsOk()) {
                        std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
                        std::string relativePath = ConvertToRelativePath(filePathName);
                        //  std::cout << "Received path: " << relativePath << std::endl;

                        try {
                            Model modelInstance;
                            std::string outputPath;
                            std::string texturePath;


                            if (relativePath.substr(relativePath.find_last_of(".") + 1) == "modelbin") {
                                outputPath = "../src/Models/" + relativePath.substr(0, relativePath.find_last_of(".")) + ".modelbin";
                                texturePath = "../src/Models";
                                modelInstance.DeserializeModel(relativePath, texturePath);
                                // std::cout << "Model Load from: " << relativePath << std::endl;
                            }
                            else {
                                modelInstance.loadModel(relativePath);
                                // std::cout << "Model Load Successful: " << relativePath << std::endl;


                                std::string fileSerializeName = relativePath.substr(relativePath.find_last_of("/") + 1);
                                texturePath = "../src/Textures/props";
                                outputPath = "../src/Models/" + fileSerializeName.substr(0, fileSerializeName.find_last_of(".")) + ".modelbin";
                                modelInstance.SerializeModel(outputPath);
                                //  std::cout << "Model Serialized to: " << outputPath << std::endl;


                            }

                            objectList.loadedModels.push_back(modelInstance);
                        }
                        catch (const std::exception& e) {
                            std::cerr << "ErrorLoadModel: " << e.what() << std::endl;
                        }


                        ImGuiFileDialog::Instance()->Close();
                        showFileDialog = false;

                    }
                    ImGuiFileDialog::Instance()->Close();
                    showFileDialog = false;
                }


            }

            ImGui::SameLine();

            if (ImGui::Button("Objects", buttonSize)) {

                ShowObjectHierarchy = !ShowObjectHierarchy;


            }
            if (ShowObjectHierarchy) {

                DrawFolderTree("src", 0);

            }


          
        });

       
}

void ContentBrowser::DrawFolderTree(const fs::path& directory, int level)
{
    try {
        if (fs::exists(directory) && fs::is_directory(directory)) {
            int i = 0;
            std::vector<fs::path> selectedPaths;  // Временный вектор для хранения одного пути
            for (const auto& entry : fs::directory_iterator(directory)) {
                if (fs::is_directory(entry)) {
                    if (ImGui::TreeNode(entry.path().filename().string().c_str())) {
                        DrawFolderTree(entry, level + 1);
                        ImGui::TreePop();
                    }
                }
                else if (fs::is_regular_file(entry)) {
                    std::string fileName = entry.path().filename().string();
                    if (fileName.size() >= 8 && fileName.substr(fileName.size() - 8) == "modelbin") {
                        std::string objectName = fileName.substr(0, fileName.find_last_of("."));
                        if (ImGui::Selectable(objectName.c_str())) {
                            selectedPaths.clear();  // Очищаем временный вектор перед добавлением нового пути
                            selectedPaths.push_back(entry.path());  // Добавляем один путь во временный вектор
                            SelectedFile(entry.path());  // Передаем временный вектор функции HandleFileSelection
                        }
                    }
                }
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}


void LoadDataFromFile(const std::string& filePath, std::vector<ContentBrowser::ObjectInfo>& data) {

    std::ifstream file(filePath, std::ios::binary);
    if (file.is_open()) {
        ContentBrowser::ObjectInfo objInfo;
        while (file.read(reinterpret_cast<char*>(&objInfo), sizeof(ContentBrowser::ObjectInfo))) {
            data.push_back(objInfo);
        }
        file.close();
        std::cout << "Data loaded from binary file." << std::endl;
    }
    else {
        std::cerr << "Failed to open file for reading." << std::endl;
    }
}

void ContentBrowser::LoadOnScene(const std::vector<fs::path>& filePaths,
                                const std::vector<glm::vec3>& initialPositions,
                                const std::vector<glm::vec3>& initialScale,
                                const std::vector<glm::vec3>& initialRotation)
{


    assert(filePaths.size() == initialPositions.size());
    assert(filePaths.size() == initialScale.size());
    assert(filePaths.size() == initialRotation.size());
   
    for (size_t i = 0; i < filePaths.size(); ++i) {
        std::string relativePath = ConvertToRelativePath(filePaths[i].string());

        if (relativePath.substr(relativePath.find_last_of(".") + 1) == "modelbin") {
            try {
                std::string texturePath = "../src/Textures/props";

                Model modelInstance;
             
                modelInstance.DeserializeModel(relativePath, texturePath);
           
                SceneObject newSceneObject(modelInstance);
               
                newSceneObject.setPosition(initialPositions[i]);
                newSceneObject.setScale(initialScale[i]);
                newSceneObject.setRotation(initialRotation[i]);
                newSceneObject.setObjectName(filePaths[i].stem().string());
                objectList.loadedModels.push_back(modelInstance);
              
              
                myScene.AddObject(newSceneObject);
              
               
            }
            catch (const std::exception& e) {
                std::cerr << "ErrorLoadModel: " << e.what() << std::endl;
            }
        }
        else {
            // Handle other types of files
        }
    }
}

void ContentBrowser::SelectedFile(const fs::path& filePath)
{
    std::string relativePath = ConvertToRelativePath(filePath.string());

    if (relativePath.substr(relativePath.find_last_of(".") + 1) == "modelbin") {
        try {
            Model modelInstance;
            std::string texturePath = "../src/Textures/props";

            modelInstance.DeserializeModel(relativePath, texturePath);
            //  std::cout << "Model Load from: " << relativePath << std::endl;

            SceneObject newSceneObject(modelInstance);
            // Set the object's name using the file name without extension
            newSceneObject.setObjectName(filePath.stem().string());

            objectList.loadedModels.push_back(modelInstance);
            myScene.AddObject(newSceneObject);
        }
        catch (const std::exception& e) {
            std::cerr << "ErrorLoadModel: " << e.what() << std::endl;
        }
    }
    else {
        // Handle other types of files
    }
}

std::string ContentBrowser::ConvertToRelativePath(const std::string& fullPath)
{
    const std::string rootPath = "../Gears/";
    size_t pos = fullPath.find(rootPath);
    std::string relativePath;
    if (pos != std::string::npos) {
        relativePath = fullPath.substr(pos + rootPath.size());
    }
    else {
        relativePath = fullPath;
    }


    for (size_t i = 0; i < relativePath.size(); i++) {
        if (relativePath[i] == '\\') {
            relativePath[i] = '/';
        }
    }

    return relativePath;
}

void ContentBrowser::DrawSceneObjects()
{
    int w, h;
    WindowScale(window, &w, &h);

    //int panelHeight = std::max(h - 2500, 150);

    DrawPanel("SceneObjects", ImVec2(0, h / 1.651), ImVec2(w / 7, 515  ), [&]()
        {
        ImGui::Text("Selected Objects");

        UpdateObjectData();

        for (int i = 0; i < myScene.objects.size(); ++i) {
            SceneObject& object = myScene.objects[i];
            std::string objectInfo = fileSerializeName + std::to_string(i);

            if (ImGui::Selectable(objectInfo.c_str(), i == selectedObjectIndex)) {
                selectedObjectIndex = i;
                objectList.setModelIndex(i);
                int index = objectList.getModelIndex();
                SceneObject& selectedObject = myScene.objects[selectedObjectIndex];
                glm::vec3 position = selectedObject.getPosition();
                glm::vec3 scale = selectedObject.getScale();
                glm::vec3 rotation = selectedObject.getRotation();


            }

            if (i == selectedObjectIndex) {
                object.setHighlightColor(glm::vec4(0.0f, 1.0f, 0.0f, 0.5f));
            }
            else {
                object.setHighlightColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
            }
        }

        if (selectedObjectIndex != -1 && ImGui::IsKeyPressed(ImGuiKey_Delete)) {
            myScene.objects.erase(myScene.objects.begin() + selectedObjectIndex);
            selectedObjectIndex = -1;
        }
       
       });
   
   
}

void ContentBrowser::DrawProperties()
{

    int w, h;
    WindowScale(window, &w, &h);

    //int panelHeight = std::max(h - 2500, 150);

    DrawPanel("Properties", ImVec2(w -  (w / 7), 150), ImVec2(w / 5, h - 195), [&]()
        {

        if (selectedObjectIndex >= 0 && selectedObjectIndex < myScene.objects.size()) {
            SceneObject& selectedObject = myScene.objects[selectedObjectIndex];
            float dragSpeed = 0.1f;

            ImGui::Text("Position");
            glm::vec3 position = selectedObject.getPosition();
            if (ImGui::DragFloat3("Position##Pos", glm::value_ptr(position), dragSpeed)) {
                selectedObject.setPosition(position);
            }

            float rotation_drag_speed = 1.0f;

            ImGui::Text("Rotation");
            glm::vec3 rotation = selectedObject.getRotation();
            if (ImGui::DragFloat3("Rotation##Rot", glm::value_ptr(rotation), rotation_drag_speed)) {
                selectedObject.setRotation(rotation);
            }

            float scale_drag_speed = 0.1f;

            ImGui::Text("Scale");
            glm::vec3 scale = selectedObject.getScale();
            if (ImGui::DragFloat3("Scale##Scale", glm::value_ptr(scale), scale_drag_speed)) {
                selectedObject.setScale(scale);
            }


            static glm::vec4 highlightColor = selectedObject.getHighlightColor();

            // Отображаем окно выбора цвета
            ImGui::ColorPicker4("SetColor", (float*)&highlightColor, ImGuiColorEditFlags_Float);

            // Устанавливаем выбранный цвет в качестве выделенного цвета объекта
            selectedObject.setHighlightColor(glm::vec4(highlightColor.r, highlightColor.g, highlightColor.b, highlightColor.a));



            // Инициализация MaterialUI для загрузки текстур
           // MaterialUI materialUI;

            std::vector<std::string> textureNames = { "Texture1" };
            std::string TextureName = textureNames[0];  // Имя текущей выбранной текстуры
            if (ImGui::BeginCombo("Texture", TextureName.c_str())) {
                ImGuiFileDialog::Instance()->OpenDialog("LoadTexture", "Load", ".jpg", ".");

                std::string selectedTexturePath;

                if (ImGuiFileDialog::Instance()->Display("LoadTexture")) {
                    if (ImGuiFileDialog::Instance()->IsOk()) {
                        selectedTexturePath = ImGuiFileDialog::Instance()->GetFilePathName();
                        //std::cout << " failed1 " << selectedTexturePath << std::endl;

                    }
                    ImGuiFileDialog::Instance()->Close();
                }

                for (const auto& textureName : textureNames) {
                    bool isSelected = (TextureName == textureName);
                    if (ImGui::Selectable(textureName.c_str(), isSelected)) {
                        TextureName = textureName;

                        //selectedObject.setTexture(selectedTexturePath);

                    }
                    if (isSelected) {
                        ImGui::SetItemDefaultFocus();  // Установим фокус на выбранный элемент
                    }
                }
                ImGui::EndCombo();
            }
        }
        else {
            ImGui::Text("No object selected.");
        }

        });
}

void ContentBrowser::AddObjectToData(int index, const glm::vec3& position, const glm::vec3& scale, const glm::vec3& rotation)
{
    ObjectInfo objInfo;
    objInfo.index = index;
    objInfo.position = position;
    objInfo.scale = scale;
    objInfo.rotation = rotation;
    objectData.push_back(objInfo);
}

void ContentBrowser::UpdateObjectData()
{
    objectData.clear(); // Очищаем данные перед обновлением

    for (int i = 0; i < myScene.objects.size(); ++i) {
        SceneObject& object = myScene.objects[i];

        int index = objectList.getModelIndex();
        glm::vec3 position = object.getPosition();
        glm::vec3 scale = object.getScale();
        glm::vec3 rotation = object.getRotation();

        // Добавляем информацию об объекте в objectData
        AddObjectToData(index, position, scale, rotation);
    }
}