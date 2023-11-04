#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;
uniform vec4 highlightColor;

void main()
{    
    vec4 textureColor = texture(texture_diffuse1, TexCoords);
    FragColor = textureColor * highlightColor;  // Умножаем цвет текстуры на цвет подсветки
}