#include "gResources.h"
#include "gCommon.h"
#include <functional>
#include <filesystem>

#include <string>
#include <fstream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Editor/gContentBrowser.h"

#include "Editor/gHeaderPanel.h"


ContentBrowser* brow = nullptr;


struct ObjectInfo {
    std::string name;
    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 rotation;
};

void Resources::LoadLevel() {

   // LOG.Log(Logger::LogLevel::INFO, "Load", NULL);
    std::vector<std::string> modelNames = { "terrain.modelbin" };
    std::vector<std::filesystem::path> multiplePaths;

    // Предполагая, что модели находятся в папке "src/Models"
    std::string modelsFolderPath = "../src/Models";

    for (const auto& modelName : modelNames) {
        std::string fullModelPath = modelsFolderPath + "/" + modelName;
        multiplePaths.emplace_back(fullModelPath);
    }

    std::vector<glm::vec3> initialPositions;
    std::vector<glm::vec3> initialScale;
    std::vector<glm::vec3> initialRotation;

   
    initialPositions.push_back(glm::vec3(0.0f, 0.0f, 0.0f)); 
   

   
    initialScale.push_back(glm::vec3(1.0f, 1.0f, 1.0f)); 
   

   
    initialRotation.push_back(glm::vec3(0.0f, 0.0f, 0.0f)); 
  

    
    brow->LoadOnScene(multiplePaths, initialPositions, initialScale, initialRotation);

}


