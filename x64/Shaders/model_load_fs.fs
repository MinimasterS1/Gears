#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

uniform sampler2D texture_diffuse1;
uniform vec4 highlightColor;
uniform vec3 baseColor; // Новая uniform-переменная для цвета без текстуры

// Переменные для направленного света
uniform vec3 dirLightDirection;
uniform vec3 dirLightAmbient;
uniform vec3 dirLightDiffuse;
uniform vec3 dirLightSpecular;

// Новые переменные для управления силой света и затуханием
uniform float lightStrength; // Сила света
uniform float attenuation;   // Затухание

void main()
{    
    vec4 textureColor = texture(texture_diffuse1, TexCoords);

    // Освещение
    vec3 lightPos = dirLightDirection * lightStrength; // Умножаем направление света на силу света
    vec3 lightColor = dirLightDiffuse;  // Используем значения для диффузного света

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float distance = length(lightPos - FragPos);
    
    // Затухание света
    float attenuationFactor = 1.0 / (1.0 + attenuation * pow(distance, 2.0));

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor * attenuationFactor;

    // Умножаем цвет текстуры на цвет подсветки и освещение
    vec3 finalColor;
    if (textureColor.a > 0.0) {
        finalColor = textureColor.rgb * (highlightColor.rgb + diffuse);
    } else {
        finalColor = baseColor * (highlightColor.rgb + diffuse);
    }

    FragColor = vec4(finalColor, 1.0);
}
