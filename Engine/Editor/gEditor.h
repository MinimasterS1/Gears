#pragma once

#include "Core/gCommon.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <functional>
#include <filesystem>

#include "iostream"



class EditorAPI {

public:

    EditorAPI() {};

    EditorAPI(GLFWwindow* window, const char* text);
    ~EditorAPI();

  
    void RenderEditor();

    void RenderConsole();

    void DrawFrameBuffer();

      int w;
      int h;

    GLFWwindow* m_Window;

    
    
    void WindowScale(GLFWwindow* window, int* width, int* height);

    void DrawPanel(const char* name, ImVec2 position, ImVec2 size, std::function<void()> contentFunc);
   

    static int  getWidth() {
        return RenderPanelWidth;
    }

    static int getHeight() {
        return RenderPanelHeight;
    }

    static int getXoffset() {
        return Offset_X;
    }

    static int getYOffset() {
        return Offset_Y;
    }

    static void setWidth(int width) {
        RenderPanelWidth = width;
    }

    static void setHeight(int height) {
        RenderPanelHeight = height;
    }


    bool DirLightProperties; 

 
    float DragStep = 0.03;

private:

    
    const char* m_Text;

    static int RenderPanelWidth;
    static int RenderPanelHeight;
    static int Offset_X;
    static int Offset_Y;

    bool ShowLoadFileDialog = false;
    bool ShowSaveFileDialog = false;





  

    
};


    

