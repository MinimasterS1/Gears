#pragma once


#ifndef CONTENT_BROWSER_H
#define CONTENT_BROWSER_H

#include "gEditor.h"

#include "Core/Containers/gObjectsList.h"
#include "Core/gObject.h"
#include <functional>
#include <filesystem>

#include "gApplication.h"

namespace fs = std::filesystem;

extern Scene& myScene;
extern ObjectList& objectList;
//extern EngineAPI_Manager& enginelight = EngineAPI_Manager::GetInstance();



class ContentBrowser : public EditorAPI
{
public:

   

    ContentBrowser(
    ) {

    
    
    };



   

    void DrawBrowser();
    void DrawFolderTree(const fs::path& directory, int level);

    void LoadOnScene(const std::vector<fs::path>& filePaths,

        const std::vector<glm::vec3>& initialPositions,
        const std::vector<glm::vec3>& initialScale,
        const std::vector<glm::vec3>& initialRotation);

    void SelectedFile(const fs::path& filePath);

    std::string ConvertToRelativePath(const std::string& fullPath);

   
  
    void DrawProperties();

    void AddObjectToData(int index, const glm::vec3& position, const glm::vec3& scale, const glm::vec3& rotation);

    void DrawSceneObjects();

    int selectedObjectIndex = -1;

    void UpdateObjectData();

    struct ObjectInfo {
        int index;

        glm::vec3 position;
        glm::vec3 scale;
        glm::vec3 rotation;
        std::string objectName;
    };


    std::vector<ObjectInfo> objectData;


    int ObjectID;

    std::string fileSerializeName;

    float DragStep = 0.03;
  
private:

    std::vector<glm::vec3> initialPositions;
    std::vector<glm::vec3> initialScale;
    std::vector<glm::vec3> initialRotation;


        
   


};

#endif 