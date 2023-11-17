#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 objectColor; // Цвет объекта
uniform float alpha;      // Прозрачность объекта

uniform vec3 lightColor;  // Цвет источника света
uniform vec3 lightPos;    // Позиция источника света
uniform vec3 viewPos;     // Позиция наблюдателя

void main()
{
    // Фоновое освещение
    float ambientStrength = 0.2;
    vec3 ambient = ambientStrength * lightColor;

    // Диффузное освещение
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Окружающий цвет
    vec3 result = (ambient + diffuse) * objectColor;

    // Добавление прозрачности
    FragColor = vec4(result, alpha);
}