#include "gConsole.h"
#include "Core/gCommon.h"


void Console::DrawConsole()
{
  
    int w, h;
    WindowScale(window, &w, &h);

    int panelHeight = std::max(h - 2500, 150);

    DrawPanel("Console", ImVec2(w / 5 , h - 195), ImVec2(1536, panelHeight), [&]()
        {

            static char inputBuffer[256] = "";
            static std::string allowedChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_-";

            const auto& logs = LOG.GetLogs();
            ImGui::BeginChild("ConsoleScrollingRegion", ImVec2(0, -ImGui::GetTextLineHeightWithSpacing()), false, ImGuiWindowFlags_HorizontalScrollbar);

            for (const auto& log : logs) {
                switch (log.level) {
                case Logger::LogLevel::ERROR:
                    ImGui::TextColored(ImVec4(1, 0, 0, 1), "[ERROR] %s", log.message.c_str());
                    break;
                case Logger::LogLevel::WARNING:
                    ImGui::TextColored(ImVec4(1, 1, 0, 1), "[WARNING] %s", log.message.c_str());
                    break;
                case Logger::LogLevel::INFO:
                    ImGui::TextColored(ImVec4(0, 1, 0, 1), "[INFO] %s", log.message.c_str());
                    break;
                case Logger::LogLevel::DEBUG:
                    ImGui::TextColored(ImVec4(0, 1, 1, 1), "[DEBUG] %s", log.message.c_str());
                    break;
                }
            }

            ImGui::EndChild();

            ImGui::Separator();
          

        
            ImGuiInputTextFlags flags = ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CallbackCharFilter;


            if (ImGui::InputText("Input", inputBuffer, IM_ARRAYSIZE(inputBuffer), flags,
                [](ImGuiInputTextCallbackData* data) -> int
                {
                    if (allowedChars.find(data->EventChar) != std::string::npos)
                        return 0;  
                    else
                        return 0;  
                }))
            {
               
                bool isNumber = true;
                for (int i = 0; inputBuffer[i] != '\0'; i++) {
                    if (!isdigit(inputBuffer[i]) && inputBuffer[i] != '.' && inputBuffer[i] != '-') {
                        isNumber = false;
                        break;
                    }
                }

                if (isNumber) {
                    double inputValue = std::stod(inputBuffer);
                    LOG.Log(Logger::LogLevel::INFO, "Input (number): ", inputValue);
                }
                else {
                    LOG.Log(Logger::LogLevel::INFO, inputBuffer, NULL);
                }

                memset(inputBuffer, 0, sizeof(inputBuffer));
            }




            
        });
}
