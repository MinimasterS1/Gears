#include "gHeaderPanel.h"
#include "Core/gCommon.h"

void HeaderPanel::DrawHeaderPanel()
{
    ImVec2 buttonSize = ImVec2(60, 25);

    int w, h;
    WindowScale(window, &w, &h);

    int panelHeight = std::max(h - 2500, 150);

    DrawPanel("Toolbar", ImVec2(0, 0), ImVec2(w, panelHeight), [&]()
        {
           

            if (ImGui::Button("Load", buttonSize)) {
                // Действия при нажатии
            }

            if (ImGui::Button("Save", buttonSize)) {
                // Действия при нажатии
            }

            if (ImGui::Button("Simulation", buttonSize)) {
                // Действия при нажатии
            }

            
        });
}
