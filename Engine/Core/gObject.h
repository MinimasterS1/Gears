#pragma once

#ifndef SCENE_OBJECT_H
#define SCENE_OBJECT_H


#include "gCommon.h"
#include "gModel.h"
#include <glm/glm.hpp>
#include <fstream>
#include "iostream"
#include <filesystem>
#include <vector>

#include "gPrimitive.h"





class SceneObject {
public:

    SceneObject() {};


    SceneObject(Model model)
        : model(model), Position(0.0f), Rotation(0.0f), Scale(1.0f), HighlightColor(1.0f, 1.0f, 1.0f, 1.0f), BaseColor (0.0f, 0.0f, 1.0f)
    {
        modelShader = Shader("../Shaders/model_load_vs.vs", "../Shaders/model_load_fs.fs");
    }

    void setPosition(const glm::vec3& pos) { Position = pos; }

    glm::vec3 getPosition() const { return Position; }

    void setRotation(const glm::vec3& rot) { Rotation = rot; }

    glm::vec3 getRotation() const { return Rotation; }

    void setScale(const glm::vec3& s) { Scale = s; }

    glm::vec3 getScale() const { return Scale; }


    glm::mat4 getTransform() const {

        glm::mat4 transform = glm::mat4(1.0f);

        transform = glm::translate(transform, Position);
        transform = glm::rotate(transform, glm::radians(Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        transform = glm::rotate(transform, glm::radians(Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        transform = glm::rotate(transform, glm::radians(Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        transform = glm::scale(transform, Scale);

        return transform;
    }
    std::vector<SceneObject> objects;

    void AddObject(const SceneObject& object) {
        objects.push_back(object);
    }

    void Draw(Camera& camera, int SCR_WIDTH, int SCR_HEIGHT) {

        camera.projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 modelMat = getTransform();
        modelShader.use();
        
        //modelShader.setUnsignedInt("textureID", textureID);
        modelShader.setMat4("projection", camera.projection);
        modelShader.setMat4("view", view);
        modelShader.setMat4("model", modelMat);
        modelShader.setVec4("highlightColor", HighlightColor);
        modelShader.setVec3("baseColor", BaseColor);
        glm::mat4 transform = getTransform();
        modelShader.setMat4("model", transform);
        model.Draw(modelShader);
      
    }

    bool hasMeshes() const { return !model.meshes.empty(); }

    void setHighlightColor(const glm::vec4& color) { HighlightColor = color; }

    glm::vec4 getHighlightColor() const { return HighlightColor; }
    Model model;

    glm::vec3 Position;
    glm::vec3 Rotation;
    glm::vec3 Scale;
    glm::vec3 BaseColor;
    glm::vec4 HighlightColor;
    std::string ObjectName;
    Shader modelShader;

    void setObjectName(const std::string& name) {
        ObjectName = name;
    }

    const std::string& getObjectName() const {
        return ObjectName;
    }


    std::string getObjectInfo() const {
      
        std::string objectInfo = "Object: " + ObjectName + "\n" +
            "Position: (" + std::to_string(Position.x) + ", " +
            std::to_string(Position.y) + ", " +
            std::to_string(Position.z) + ")\n" +
            "Rotation: (" + std::to_string(Rotation.x) + ", " +
            std::to_string(Rotation.y) + ", " +
            std::to_string(Rotation.z) + ")\n" +
            "Scale: (" + std::to_string(Scale.x) + ", " +
            std::to_string(Scale.y) + ", " +
            std::to_string(Scale.z) + ")";

        return objectInfo;
    }

};

#endif SCENE_OBJECT_H


#ifndef SCENE_H
#define SCENE_H


class Scene {
public:

    Scene() {}

    std::vector<SceneObject> objects;

    void AddObject(const SceneObject& object) {
        objects.push_back(object);
    }

    void LogSceneObjectsInfo() const {
        for (const SceneObject& object : objects) {
           
            std::string objectInfo = object.getObjectInfo();
           
            LOG.Log(Logger::LogLevel::INFO, objectInfo.c_str(), NULL);
        }
    }
    static Scene& Instance() {
        static Scene instance;
        return instance;
    }
 
};


#endif SCENE_



