#include "gEditor.h"

#include "Core/gCommon.h"
#include "gHeaderPanel.h"
#include "gConsole.h"
#include "gContentBrowser.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Core/gVideoMg.h>

HeaderPanel* headerPanel = nullptr;
Console* console = nullptr;
ContentBrowser* browser = nullptr;


int EditorAPI::RenderPanelWidth = 1580;
int EditorAPI::RenderPanelHeight = 1090;
int EditorAPI::Offset_X = 0;
int EditorAPI::Offset_Y = 150;


EditorAPI::EditorAPI(GLFWwindow* window, const char* text)
{
    IMGUI_CHECKVERSION();

    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.FontGlobalScale = 1.0f;

    ImFont* myFont = io.Fonts->AddFontFromFileTTF("../src/font/Univers.ttf", 18.0f);

    if (myFont == nullptr) { LOG.Log(Logger::LogLevel::ERROR, "Error set Font ", NULL); }


    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.08f, 0.69f, 0.63f, 1.0f));  //text color
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(50, 50, 50, 255)); // buttons color
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.05f, 0.05f, 0.05f, 1.0f)); //window color
    ImVec4 inactiveTitleBg = ImGui::GetStyleColorVec4(ImGuiCol_TitleBg);
    ImGui::PushStyleColor(ImGuiCol_TitleBgActive, inactiveTitleBg);
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.7f, 0.7f, 0.7f, 1.0f));
    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 5.0f; 
    style.FrameRounding = 2.0f;

    bool allInitialized = true; 

    if (allInitialized) {
        
       headerPanel = new HeaderPanel();
       console = new Console();
       browser = new ContentBrowser();
    }

}

EditorAPI::~EditorAPI()
{

    ImGui_ImplOpenGL3_Shutdown();

    ImGui_ImplGlfw_Shutdown();

    ImGui::DestroyContext();

}

void EditorAPI::RenderEditor()
{
    // WindowScale(m_Window, &w, &h);

    ImVec2 windowSize = ImGui::GetIO().DisplaySize;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    if (EditorMode)
    {
        headerPanel->DrawHeaderPanel();
        console->DrawConsole();
        browser->DrawBrowser();
        browser->DrawSceneObjects();
        browser->DrawProperties();
        DrawFrameBuffer();

    }

    
    ImGui::Render();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
   
}

void EditorAPI::RenderConsole()
{
    // WindowScale(m_Window, &w, &h);

    ImVec2 windowSize = ImGui::GetIO().DisplaySize;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

   
    if (!GameConsole)
    {
        console->DrawConsole();
    }

   


    ImGui::Render();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void EditorAPI::DrawFrameBuffer()
{
    int w, h;
   WindowScale(window, &w, &h);

   

    ImGui::SetNextWindowPos(ImVec2(w / 7, 150));

    ImGui::SetNextWindowSize(ImVec2(w - (w / 3.5), h - 345));

    ImGuiStyle& default_style = ImGui::GetStyle();
    ImVec4 default_window_bg = default_style.Colors[ImGuiCol_WindowBg];

    ImGuiStyle& style = ImGui::GetStyle();

    style.Colors[ImGuiCol_WindowBg].w = 0.0f;

    ImGui::Begin("Background Window", nullptr, ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoTitleBar);


    ImGui::Text("FPS: %.1f", VideoAPI::getFPS());



    // ImGui::Text("Time: %.1f", VideoManager::GetSimTime());



    ImGui::Text("Polys: %.1f", "0");


    ImGui::Text("Vertex: %.1f", "0");

    ImGui::End();

    style.Colors[ImGuiCol_WindowBg] = default_window_bg;

      
}

void EditorAPI::WindowScale(GLFWwindow* window, int* width, int* height)
{
    {

        {
            if (window == NULL) {

                LOG.Log(Logger::LogLevel::INFO, "now window", NULL);
                return;
               
            }

            glfwGetWindowSize(window, width, height);

            if (width && height) {

                w = *width;
                h = *height;

               // LOG.Log(Logger::LogLevel::INFO, "Scale", *width);

            }

        }
    }
}

void EditorAPI::DrawPanel(const char* name, ImVec2 position, ImVec2 size, std::function<void()> contentFunc)
{
    {

        ImGuiWindowFlags flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize;
       

        ImGui::SetNextWindowPos(position);
        ImGui::SetNextWindowSize(size);

        if (ImGui::Begin(name, nullptr, flags))
        {
            contentFunc();
            ImGui::End();
        }
    }
}

