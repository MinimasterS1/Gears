#pragma once

#ifndef VIDEOAPI_H
#define VIDEOAPI_H

#include "gCommon.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <iostream>


#include "gInputMg.h"


extern float LastX;
extern float LastY;
extern bool FirstMouse;



#define GL_CHECK(stmt) do { \
        stmt; \
        CheckOpenGLError(#stmt, __FILE__, __LINE__); \
    } while (0)


bool fileExists(const std::string& filename);

class VideoAPI

{
public:

    VideoAPI() {};


    ~VideoAPI()
    {
        InputManager->shutDown();
        delete InputManager;
    }


    inline static int SCR_WIDTH;
    inline static int SCR_HEIGHT;

    static float getFPS() {
        return FPS;
    }

    void startUp();
 
    void shutDown();
   

    void update();
  

    static void framebuffer_size_callback_static(GLFWwindow* window, int width, int height)

    {
        VideoAPI* videoManager = static_cast<VideoAPI*>(glfwGetWindowUserPointer(window));
        if (videoManager)
        {
            videoManager->framebuffer_size_callback(window, width, height);
        }
    }

    bool ShouldClose() {
        return glfwWindowShouldClose(window);
    }

    void CreateWindow();

    void Render();

    void framebuffer_size_callback(GLFWwindow* window, int width, int height);
  
    void GL_Check(const char* label);

  

private:


    Input* InputManager;

    static float FPS;
    static float DeltaTime;
    static float LastFrame;
    GLFWwindow* window;
};



#endif

