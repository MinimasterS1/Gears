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

#include "Editor/gEditor.h"
#include "gInputMg.h"

#include "gLighting.h"


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
    VideoAPI() : EditorUI(nullptr)
    {

    }

    ~VideoAPI()
    {
        InputManager->shutDown();
        delete InputManager;
    }


    inline static int SCR_WIDTH;
    inline static int SCR_HEIGHT;

    Lighting DirectionalLight;
    
    std::function<void(unsigned int codepoint)> on_char;
    std::function<void(int key, int action, int mods)> on_key;
    std::function<void(int button, int action, int mods)> on_mouse_button;
    std::function<void(linalg::aliases::float2 pos)> on_cursor_pos;
    std::function<void(int numFiles, const char** paths)> on_drop;


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

    GLFWwindow* get_glfw_window_handle() { return window; };
    bool should_close() const { return !!glfwWindowShouldClose(window); }
    int get_window_attrib(int attrib) const { return glfwGetWindowAttrib(window, attrib); }
    linalg::aliases::int2 get_window_size() const { linalg::aliases::int2 size; glfwGetWindowSize(window, &size.x, &size.y); return size; }
    void set_window_size(linalg::aliases::int2 newSize) { glfwSetWindowSize(window, newSize.x, newSize.y); }
    linalg::aliases::int2 get_framebuffer_size() const { linalg::aliases::int2 size; glfwGetFramebufferSize(window, &size.x, &size.y); return size; }
    linalg::aliases::float2 get_cursor_pos() const { linalg::aliases::double2 pos; glfwGetCursorPos(window, &pos.x, &pos.y); return linalg::aliases::float2(pos); }

    void swap_buffers() { glfwSwapBuffers(window); }
    void close() { glfwSetWindowShouldClose(window, 1); }





  
private:

    
    Input* InputManager;
    std::unique_ptr<EditorAPI> EditorUI;
    static float FPS;
    static float DeltaTime;
    static float LastFrame;


  
   
};



#endif

