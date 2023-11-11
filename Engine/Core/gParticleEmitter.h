#pragma once
#pragma once

#include "gParticle.h"

#include <vector>
#include <random>
#include "gShader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

class ParticleEmitter {
public:

    ParticleEmitter() {};

    std::vector<Particle> particles;
    unsigned int VAO, VBO;

    std::default_random_engine generator;
    std::uniform_real_distribution<float> distribution{-10.0, 10.0}; // диапазон случайных чисел

    ParticleEmitter(int numParticles) ;

      
    
    void Update(float deltaTime);

    void Draw(Shader& shader, glm::mat4 projection, glm::mat4 view);
       

    

    float getLifetime() const {
        return lifetime;
    }
    void setLifetime(float newLifetime) {

        lifetime = newLifetime;
        //  for (Particle& p : particles) {
         //     p.lifetime = newLifetime;
         // }
    }

    glm::vec4 getColor() const {
        return color; 
    }
    void setColor(const glm::vec4& newColor);
      
    

    float getPointSize() {
        return pointSize;
    }
    void setPointSize(float newSize) {
        pointSize = newSize;
    }

    void setGravity(glm::vec3 newGravity) {
        gravity = newGravity;
    }

    void setWind(glm::vec3 newWind) {
        wind = newWind;
    }

    void setSpawnPosition(glm::vec3 newPosition) {
        spawnPosition = newPosition;
    }

    void setAge(float newAge) {
        age = newAge;
    }

    void setDelay(float newDelay) {
        Delay = newDelay;
    }

    void setDirection(glm::vec3 newDirection) {
        direction = newDirection;
    }

    void setMaxAge(float newMaxAge) {
        MaxAge = newMaxAge;
    }



private:

    glm::vec4 color;
    float lifetime = 1.0f;
    float pointSize;
    glm::vec3 spawnPosition;
    glm::vec3 direction;
    glm::vec3 gravity, wind;
    float age;
    float Delay;
    float MaxAge;
};
