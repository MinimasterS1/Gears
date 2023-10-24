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


private:

    Camera& camera;
    float Last_X, Last_Y;
    bool FirstMouse;

};

#endif