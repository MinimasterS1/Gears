#pragma once

#ifndef INPUTAPI_H
#define INPUTAPI_H

#include "gCommon.h"

#include <GLFW/glfw3.h>

class Input {
public:



    Input(Camera& camera);

    ~Input();

    void startUp();

    void shutDown();

    void update(GLFWwindow* window, float deltaTime);

    void MouseCallback(GLFWwindow* window, double xpos, double ypos);

    void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

    void ProcessInput(GLFWwindow* window, float deltaTime);

    void ProcessSingleKeyPress(GLFWwindow* window, int key, int action);


    float Lerp(float a, float b, float t) {
        // Убедитесь, что t находится в диапазоне от 0 до 1
        t = glm::clamp(t, 0.0f, 1.0f);

        // Выполняем интерполяцию
        return a + t * (b - a);
    }

private:

    Camera& camera;
    float Last_X, Last_Y;
    bool FirstMouse;

    int previousKeyState[GLFW_KEY_LAST + 1];
    bool keyQPressed = false;

};

#endif