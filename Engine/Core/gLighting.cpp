#include "gLighting.h"



Lighting::Lighting()
    : directionalLightDirection(glm::vec3(0.0f, 5.0f, 0.0f)),  // Пример начального значения для направления света
    directionalLightColor(glm::vec3(1.0f, 2.0f, 1.0f)),       // Пример начального значения для цвета света
    directionalLightAmbient(glm::vec3(0.2f)),
    directionalLightDiffuse(glm::vec3(1.0f)),
    directionalLightSpecular(glm::vec3(0.5f))

{


}

void Lighting::initialize()
{
    setDirectionalLight(glm::vec3(1.0f, 1.0f, 1.0f) ,glm::vec3(5.0f, 5.0f,5.0f), glm::vec3(0.2f), glm::vec3(1.0f), glm::vec3(0.5f));

    // Установка параметров точечного света
   // setPointLight(glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(0.2f), glm::vec3(1.0f), glm::vec3(0.5f), 1.0f, 0.09f, 0.032f);

    // Установка параметров прожекторного света
  // setSpotLight(glm::vec3(0.0f, 3.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.2f), glm::vec3(1.0f), glm::vec3(0.5f), 1.0f, 0.09f, 0.032f, glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(17.5f)));
}

void Lighting::setDirectionalLight(const glm::vec3& color, const glm::vec3& direction, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular)
{
    directionalLightColor = color;
    directionalLightDirection = direction;
    directionalLightAmbient = ambient;
    directionalLightDiffuse = diffuse;
    directionalLightSpecular = specular;
}

void Lighting::setPointLight(const glm::vec3& position, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, float constant, float linear, float quadratic)
{
}

void Lighting::setSpotLight(const glm::vec3& position, const glm::vec3& direction, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, float constant, float linear, float quadratic, float cutOff, float outerCutOff)
{
}

void Lighting::applyLighting(const Shader& shader)
{
    
    shader.setFloat("lightStrength", Stregth);
    shader.setFloat("attenuation", Attenuation);

    shader.setVec3("dirLightDirection", directionalLightDirection);
    shader.setVec3("dirLightAmbient", directionalLightColor * directionalLightAmbient);
    shader.setVec3("dirLightDiffuse", directionalLightColor * directionalLightDiffuse);
    shader.setVec3("dirLightspecular", directionalLightColor * directionalLightSpecular);

    // Передача параметров точечного света в шейдер
    shader.setVec3("pointLight.position", pointLightPosition);
    shader.setVec3("pointLight.ambient", pointLightAmbient);
    shader.setVec3("pointLight.diffuse", pointLightDiffuse);
    shader.setVec3("pointLight.specular", pointLightSpecular);
    shader.setFloat("pointLight.constant", pointLightConstant);
    shader.setFloat("pointLight.linear", pointLightLinear);
    shader.setFloat("pointLight.quadratic", pointLightQuadratic);

    // Передача параметров прожекторного света в шейдер
    shader.setVec3("spotLight.position", spotLightPosition);
    shader.setVec3("spotLight.direction", spotLightDirection);
    shader.setVec3("spotLight.ambient", spotLightAmbient);
    shader.setVec3("spotLight.diffuse", spotLightDiffuse);
    shader.setVec3("spotLight.specular", spotLightSpecular);
    shader.setFloat("spotLight.constant", spotLightConstant);
    shader.setFloat("spotLight.linear", spotLightLinear);
    shader.setFloat("spotLight.quadratic", spotLightQuadratic);
    shader.setFloat("spotLight.cutOff", spotLightCutOff);
    shader.setFloat("spotLight.outerCutOff", spotLightOuterCutOff);

    // Передача параметров материала в шейдер
    shader.setVec3("material.ambient", materialAmbient);
    shader.setVec3("material.diffuse", materialDiffuse);
    shader.setVec3("material.specular", materialSpecular);
    shader.setFloat("material.shininess", materialShininess);
}

void Lighting::setMaterial(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, float shininess)
{
    materialAmbient = ambient;
    materialDiffuse = diffuse;
    materialSpecular = specular;
    materialShininess = shininess;
}
