#pragma once


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "gShader.h"

class Lighting
{
public:
    Lighting();
    

    void initialize();

  
    void setDirectionalLight(const glm::vec3& color, const glm::vec3& direction, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular);

    void setPointLight(const glm::vec3& position, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular,
        float constant, float linear, float quadratic);

    void setSpotLight(const glm::vec3& position, const glm::vec3& direction, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular,
        float constant, float linear, float quadratic, float cutOff, float outerCutOff);

    void applyLighting(const Shader& shader);

    void setMaterial(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, float shininess);

   
    glm::vec3 directionalLightDirection;  
    glm::vec3 directionalLightColor;      
    glm::vec3 directionalLightAmbient;
    glm::vec3 directionalLightDiffuse;
    glm::vec3 directionalLightSpecular;
    
    float Stregth;
    float Attenuation;



    float getDirectionalLightStrength() const { return Stregth; }
    void setDirectionalLightStrength(const float& strength) { Stregth = strength; }

    float getDirectionalLightAttenuationh() const { return  Attenuation; }
    void setDirectionalLightAttenuation(const float& attenuation) { Attenuation = attenuation; }

    glm::vec3 getDirectionalLightDirection() const { return directionalLightDirection; }
    void setDirectionalLightDirection(const glm::vec3& direction) { directionalLightDirection = direction; }

    glm::vec3 getDirectionalLightColor() const { return directionalLightColor; }
    void setDirectionalLightColor(const glm::vec3& color) { directionalLightColor = color; }

    glm::vec3 getDirectionalLightAmbient() const { return directionalLightAmbient; }
    void setDirectionalLightAmbient(const glm::vec3& ambient) { directionalLightAmbient = ambient; }

    glm::vec3 getDirectionalLightDiffuse() const { return directionalLightDiffuse; }
    void setDirectionalLightDiffuse(const glm::vec3& diffuse) { directionalLightDiffuse = diffuse; }

    glm::vec3 getDirectionalLightSpecular() const { return directionalLightSpecular; }
    void setDirectionalLightSpecular(const glm::vec3& specular) { directionalLightSpecular = specular; }



private:
    // Параметры направленного света
    
  
  

    // Параметры точечного света
    glm::vec3 pointLightPosition;
    glm::vec3 pointLightAmbient;
    glm::vec3 pointLightDiffuse;
    glm::vec3 pointLightSpecular;
    float pointLightConstant;
    float pointLightLinear;
    float pointLightQuadratic;

    // Параметры прожекторного света
    glm::vec3 spotLightPosition;
    glm::vec3 spotLightDirection;
    glm::vec3 spotLightAmbient;
    glm::vec3 spotLightDiffuse;
    glm::vec3 spotLightSpecular;
    float spotLightConstant;
    float spotLightLinear;
    float spotLightQuadratic;
    float spotLightCutOff;
    float spotLightOuterCutOff;

    glm::vec3 materialAmbient;
    glm::vec3 materialDiffuse;
    glm::vec3 materialSpecular;
    float materialShininess;
};
