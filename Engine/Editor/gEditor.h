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


    GLFWwindow* m_Window;

private:

    
    const char* m_Text;

    static int RenderPanelWidth;
    static int RenderPanelHeight;
    static int Offset_X;
    static int Offset_Y;

    bool ShowLoadFileDialog = false;
    bool ShowSaveFileDialog = false;

};


class Panel {


private:

    std::string name;
    ImVec2 pos;
    ImVec2 size;



public:

    Panel() {};

    int flags;

    Panel(const std::string& panelName, const ImVec2& position, const ImVec2& panelSize, int windowFlags = 0)
        : name(panelName), pos(position), size(panelSize), flags(windowFlags)
    {
        // flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize;
    }

    void Draw(std::function<void()> contentFunc, GLFWwindow* window);

    static bool editWindowEnabled;


};