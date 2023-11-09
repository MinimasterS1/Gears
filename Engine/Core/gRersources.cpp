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

    // Задаем координаты для каждого объекта
    initialPositions.push_back(glm::vec3(0.0f, 0.0f, 0.0f)); // Первый объект
   // initialPositions.push_back(glm::vec3(-19.0f, 3.0f, 11.3f)); // Второй объект

    // Задаем масштаб для каждого объекта
    initialScale.push_back(glm::vec3(1.0f, 1.0f, 1.0f)); // Первый объект
   // initialScale.push_back(glm::vec3(7.6f, 0.1f, 19.8f)); // Второй объект

    // Задаем вращение для каждого объекта
    initialRotation.push_back(glm::vec3(0.0f, 0.0f, 0.0f)); // Первый объект
   // initialRotation.push_back(glm::vec3(0.0f, 0.0f, 0.0f)); // Второй объект

    // Вызываем LoadOnScene только один раз после заполнения всех данных
    brow->LoadOnScene(multiplePaths, initialPositions, initialScale, initialRotation);

}


