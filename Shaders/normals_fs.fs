#version 330 core
out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec2 TexCoords;
    vec3 TangentLightPos;
    vec3 TangentViewPos;
    vec3 TangentFragPos;
} fs_in;

uniform sampler2D diffuseMap;
uniform sampler2D normalMap;

uniform float specularStrength;
uniform float normalStrength;
uniform float lightIntensity;
uniform float reflectivity;
uniform float transparency;

uniform vec3 ambientLight;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{           
    // Получаем нормаль из карты нормалей с диапазоном [0,1]
    vec3 normal = texture(normalMap, fs_in.TexCoords).rgb;
    
    // Усиление или ослабление эффекта карты нормалей
    normal = normalize(normal * 2.0 - 1.0) * normalStrength;
    
    // Получаем диффузный цвет
    vec3 color = texture(diffuseMap, fs_in.TexCoords).rgb;

    // Фоновая составляющая
    vec3 ambient = ambientLight * color;

    // Диффузная составляющая
    vec3 lightDir = normalize(fs_in.TangentLightPos - fs_in.TangentFragPos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * color;

    // Отраженная составляющая
    vec3 viewDir = normalize(fs_in.TangentViewPos - fs_in.TangentFragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);
    vec3 specular = specularStrength * vec3(0.1) * spec * reflectivity; // учтено отражение

    // Итоговый цвет
    FragColor = vec4(ambient + diffuse + specular, transparency); // учтена прозрачность
}