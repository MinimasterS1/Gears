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
           

            if (ImGui::Button("Load Level", buttonSize)) {
                
                loadLevel.LoadLevel();
            }

            if (ImGui::Button("Save Level", buttonSize))
            
            {

               SaveObjectsToBinaryFile(my.objects, "level_data.bin");

               
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

                      

                        ImGuiFileDialog::Instance()->Close();
                        ShowSaveFileDialog = false;
                    }

                    ImGuiFileDialog::Instance()->Close();
                }
            }

            if (ImGui::Button("Simulation", buttonSize)) {
                // Действия при нажатии
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
            file.write(object.objectName.c_str(), object.objectName.size() + 1);
            file.write(reinterpret_cast<const char*>(&object.position), sizeof(glm::vec3)); 
            file.write(reinterpret_cast<const char*>(&object.rotation), sizeof(glm::vec3)); 
            file.write(reinterpret_cast<const char*>(&object.scale), sizeof(glm::vec3)); 
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
                object.objectName = objectName;
                file.read(reinterpret_cast<char*>(&object.position), sizeof(glm::vec3));
                file.read(reinterpret_cast<char*>(&object.rotation), sizeof(glm::vec3));
                file.read(reinterpret_cast<char*>(&object.scale), sizeof(glm::vec3));
                loadedObjects.push_back(object);
            }

            file.close();
        }

        return loadedObjects;
    }

