#include "gHeaderPanel.h"
#include "Core/gCommon.h"
#include "ImGuiFileDialog.h"
#include "Core/gResources.h"

#include "Core/Containers/gObjectsList.h"



Resources loadLevel;
Scene& my = Scene::Instance();

ObjectList& object = ObjectList::getInstance();



void HeaderPanel::DrawHeaderPanel()
{
    ImVec2 buttonSize = ImVec2(65, 25);

    int w, h;
    WindowScale(window, &w, &h);

    int panelHeight = std::max(h - 2500, 150);

    DrawPanel("Toolbar", ImVec2(0, 0), ImVec2(w, panelHeight), [&]()
        {
           
         

            if (ImGui::Button("Load ", buttonSize)) {
                
                loadLevel.LoadLevel();
            }

            if (ImGui::Button("Save", buttonSize))
            {
                if (currentTab == PARTICLE)
                {
                    ImGuiFileDialog::Instance()->OpenDialog("SaveFileDlgKey", "Save File", ".part", ".");
                    ShowSaveFileDialog = true;
                }

                if (currentTab == LEVEL)
                {
                    ImGuiFileDialog::Instance()->OpenDialog("SaveFileDlgKey", "Save File", ".lvl", ".");
                    ShowSaveFileDialog = true;
                }
              
            }


            if (ShowSaveFileDialog)
            {
                // Prepare file dialog
                if (ImGuiFileDialog::Instance()->Display("SaveFileDlgKey"))
                {
                    if (ImGuiFileDialog::Instance()->IsOk())
                    {
                        std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
                        std::cout << "Save file: " << filePathName << std::endl;

                        // Создайте пустой файл в зависимости от текущего типа файла
                        if (currentFileType == FILE_PART)
                        {
                            if (filePathName.find(".part") != std::string::npos)
                            {
                                std::ofstream outputFile(filePathName, std::ios::binary);

                                if (outputFile.is_open())
                                {
                                    outputFile.close();
                                }
                                else
                                {
                                    // Обработка ошибки: не удалось создать файл
                                    // Вы можете добавить здесь код обработки ошибки по вашему усмотрению
                                }
                            }
                        }
                        else if (currentFileType == FILE_LVL)
                        {

                            
                        }
                        else if (currentFileType == FILE_MAT)
                        {
                            // Создайте пустой файл .mat
                        }
                        // Другие условия для других типов файлов
                        // ...

                        ImGuiFileDialog::Instance()->Close();
                        ShowSaveFileDialog = false;
                    }

                    ImGuiFileDialog::Instance()->Close();
                }
            }


            if (ImGui::Button("Simulation", buttonSize)) {
                // Действия при нажатии
            }


            ImGui::SameLine(w / 2 - 4 * buttonSize.x / 2);

            if (ImGui::Button("Level", buttonSize)) {
                currentTab = LEVEL;
            }

            ImGui::SameLine();

            if (ImGui::Button("Materials", buttonSize)) {
                currentTab = MATERIAL;
            }

            ImGui::SameLine();

            if (ImGui::Button("Particles", buttonSize)) {
                currentTab = PARTICLE;
            }

            ImGui::SameLine();

            if (ImGui::Button("Animations", buttonSize)) {
                currentTab = ANIMATION;
            }


            
        });
}

void HeaderPanel::SaveObjectsToBinaryFile(const std::vector<SceneObject>& objects, const std::string& filename)
{
    std::ofstream file(filename, std::ios::binary);
    if (file.is_open()) {
       
        int numObjects = static_cast<int>(objects.size());
        file.write(reinterpret_cast<const char*>(&numObjects), sizeof(int));

      
        for (const SceneObject& object : objects) {
            file.write(object.ObjectName.c_str(), object.ObjectName.size() + 1);
            file.write(reinterpret_cast<const char*>(&object.Position), sizeof(glm::vec3)); 
            file.write(reinterpret_cast<const char*>(&object.Rotation), sizeof(glm::vec3)); 
            file.write(reinterpret_cast<const char*>(&object.Scale), sizeof(glm::vec3)); 
        }

        file.close();
    }
}


std::vector<SceneObject> HeaderPanel::LoadObjectsFromBinaryFile(const std::string & filename) {
        std::vector<SceneObject> loadedObjects;
        std::ifstream file(filename, std::ios::binary);

        if (file.is_open()) {
            int numObjects = 0;
            file.read(reinterpret_cast<char*>(&numObjects), sizeof(int));

            for (int i = 0; i < numObjects; ++i) {
                SceneObject object;
                char objectName[256];
                file.read(objectName, 256);
                object.ObjectName = objectName;
                file.read(reinterpret_cast<char*>(&object.Position), sizeof(glm::vec3));
                file.read(reinterpret_cast<char*>(&object.Rotation), sizeof(glm::vec3));
                file.read(reinterpret_cast<char*>(&object.Scale), sizeof(glm::vec3));
                loadedObjects.push_back(object);
            }

            file.close();
        }

        return loadedObjects;
    }

