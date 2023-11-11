#include "gCommon.h"

#include "gParticleEditor.h"


void ParticleUI::DrawEmitterSettings()
{

    static bool colorAuto = false;
    static ImVec4 particleColor;

    static bool directionAuto = false;
    static float direction[3];

    static bool lifetimeAuto = false;
    static float lifetime;

    static bool countAuto = false;
    static int particleCount;

    static bool sizeAuto = false;

    int w, h;
    WindowScale(window, &w, &h);

    int panelHeight = std::max(h - 2500, 150);

    ImVec2 buttonSize = ImVec2(50, 30);

    DrawPanel("Emitter", ImVec2(w - (w / 6), 150), ImVec2(w / 5, h - 195), [&]()
        {


            ImGui::Text("Color Settings");

            static float colorInterpolationSpeed = 0.01f;
            static float t_color = 0.0f;


            ImGui::ColorEdit4("Min Color", (float*)&minColor);
            ImGui::ColorEdit4("Max Color", (float*)&maxColor);


            ImGui::SliderFloat("Color Interpolation Speed", &colorInterpolationSpeed, 0.001f, 0.1f);


            if (ImGui::Checkbox("Random in range", &colorAuto)) {

            }

            glm::vec4 currentColor;

            if (!colorAuto) {
                if (ImGui::ColorEdit4("Particle Color", (float*)&currentColor)) {
                    // RenderManager::setColor(currentColor);
                }
            }
            else {
                t_color += colorInterpolationSpeed;
                if (t_color > 1.0f) t_color = 0.0f;

                // Интерполяция цвета
                glm::vec4 interpolatedColor = (1.0f - t_color) * minColor + t_color * maxColor;
                // RenderManager::setColor(interpolatedColor);
            }



            ImGui::Separator();


            ImGui::Text("Lifetime Settings");
            static bool lifetimeAuto;
            if (ImGui::Checkbox("Auto Lifetime", &lifetimeAuto)) {
                if (lifetimeAuto) {

                }
            }
            if (!lifetimeAuto) {


                if (ImGui::InputFloat("Lifetime", &currentLifetime)) {

                    //RenderManager::setLifetime(currentLifetime);
                }
            }


            ImGui::Separator();



            // Count Settings
            ImGui::Text("Count Settings");
            ImGui::Checkbox("Auto Count", &countAuto);
            if (!countAuto) {
                ImGui::InputInt("Particle Count", &particleCount);
            }
            ImGui::Separator();

            ImGui::Text("Size Settings");
            static bool sizeAuto = false; // Флаг для автоматического режима
            static float minPointSize = 1.0f; // Минимальный размер
            static float maxPointSize = 10.0f; // Максимальный размер
            static float interpolationSpeed = 0.01f; // Скорость интерполяции
            static float currentPointSize;

            // Обновление временного параметра
            static float t = 0.0f;
            t += interpolationSpeed;
            if (t > 1.0f) t = 0.0f;

            ImGui::InputFloat("Min Point Size", &minPointSize); // Ввод минимального размера
            ImGui::InputFloat("Max Point Size", &maxPointSize); // Ввод максимального размера
            ImGui::SliderFloat("Interpolation Speed", &interpolationSpeed, 0.001f, 0.1f); // Слайдер для скорости интерполяции

            if (ImGui::Checkbox("Auto Size", &sizeAuto)) {
                // Логика для автоматического изменения размера
            }

            if (!sizeAuto) {
                ImGui::InputFloat("Particle Size", &currentPointSize);
                // RenderManager::setSize(currentPointSize);
            }
            else {
                // Используем линейную интерполяцию для вычисления размера
                float interpolatedSize = (1.0f - t) * minPointSize + t * maxPointSize;
                //RenderManager::setSize(interpolatedSize);
            }

            ImGui::Separator();

            // Spawn Coordinates
            ImGui::Text("Spawn Coordinates");
            static float spawnCoords[3];
            if (ImGui::InputFloat3("Spawn Position", spawnCoords)) {
                // Обновите координаты спавна в вашем менеджере рендеринга или эмиттере
              //  RenderManager::setSpawn(glm::vec3(spawnCoords[0], spawnCoords[1], spawnCoords[2]));
            }

            ImGui::Separator();

            // Gravity Settings
            ImGui::Text("Gravity Settings");
            static float gravity[3];
            if (ImGui::InputFloat3("Gravity", gravity)) {
                // Обновите вектор гравитации
               // RenderManager::setGravity(glm::vec3(gravity[0], gravity[1], gravity[2]));
            }

            ImGui::Separator();



            ImGui::Text("Direction Settings");
            static float direction[3];
            static float minDirection[3] = { -1.0f, -1.0f, -1.0f }; // минимальные значения диапазона для X, Y, Z
            static float maxDirection[3] = { 1.0f, 1.0f, 1.0f }; // максимальные значения диапазона для X, Y, Z
            static bool autoRandomize = false; // флаг для автоматической рандомизации

            if (ImGui::Checkbox("Auto Randomize Direction", &autoRandomize)) {
                // Логика для автоматической рандомизации направления, если требуется
            }

            if (!autoRandomize) {
                ImGui::InputFloat3("Direction", direction);

                ImGui::InputFloat3("Min Direction", minDirection);
                ImGui::InputFloat3("Max Direction", maxDirection);
            }
            else {

            }

            if (ImGui::Button("Randomize Direction")) {


            }

            ImGui::Separator();

            ImGui::Text("Delay Settings");
            static float delay;
            if (ImGui::InputFloat("Delay", &delay)) {

            }

            // Age Settings
            ImGui::Text("Age Settings");
            static float age;
            if (ImGui::InputFloat("Age", &age)) {

            }


            ImGui::Text("MaxAge Settings");
            static float maxAge;
            if (ImGui::InputFloat("MaxAge", &maxAge)) {

            }




        });

}

