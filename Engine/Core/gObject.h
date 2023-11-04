#pragma once

#ifndef SCENE_OBJECT_H
#define SCENE_OBJECT_H

#include "gCommon.h"
#include "gModel.h"
#include <glm/glm.hpp>
#include <fstream>
#include "iostream"


class SceneObject {
public:

    SceneObject() {};

    SceneObject(Model model)
        : model(model), position(0.0f), rotation(0.0f), scale(1.0f), highlightColor(0.0f, 1.0f, 0.0f, 1.0f)
    {
        modelShader = Shader("Shaders/model_load_vs.vs", "Shaders/model_load_fs.fs");

    }

    void setPosition(const glm::vec3& pos) { position = pos; }
    glm::vec3 getPosition() const { return position; }
    void setRotation(const glm::vec3& rot) { rotation = rot; }
    glm::vec3 getRotation() const { return rotation; }
    void setScale(const glm::vec3& s) { scale = s; }
    glm::vec3 getScale() const { return scale; }


    glm::mat4 getTransform() const {
        glm::mat4 transform = glm::mat4(1.0f);
        transform = glm::translate(transform, position);
        transform = glm::rotate(transform, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        transform = glm::rotate(transform, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        transform = glm::rotate(transform, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        transform = glm::scale(transform, scale);
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
        modelShader.setVec4("highlightColor", highlightColor);
        glm::mat4 transform = getTransform();
        modelShader.setMat4("model", transform);
        model.Draw(modelShader);

    }

    bool hasMeshes() const { return !model.meshes.empty(); }
    void setHighlightColor(const glm::vec4& color) { highlightColor = color; }
    glm::vec4 getHighlightColor() const { return highlightColor; }

    Model model;
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    glm::vec4 highlightColor;

    Shader modelShader;

    void setObjectName(const std::string& name) {
        objectName = name;
    }


private:

    std::string objectName;
    std::string texturePath;

};

#endif SCENE_OBJECT_H

#ifndef SCENE_H
#define SCENE_H

class Scene {
public:
    std::vector<SceneObject> objects;

    void AddObject(const SceneObject& object) {
        objects.push_back(object);
    }

    static Scene& Instance() {
        static Scene instance;
        return instance;
    }
private:

    Scene() {}

};
#endif SCENE_H