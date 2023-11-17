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

    ParticleEmitter(int numParticles) {

        particles.resize(numParticles);

        for (Particle& p : particles) {
            p.position = glm::vec3(distribution(generator), distribution(generator), distribution(generator));
            p.position = glm::vec3(0.0f, 0.0f, 0.0f);
            p.color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f); // белый цвет, непрозрачный
            p.velocity = glm::vec3(0.1f, 0.1f, 0.1f);
            p.Lifetime = 5.0f;
            p.Age = 3.0f;
        }
        // Инициализация OpenGL Buffers
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Particle) * particles.size(), &particles[0], GL_DYNAMIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)0); // position

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)(sizeof(glm::vec3))); // color

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void Update(float deltaTime) {


        for (Particle& p : particles) {

            p.Age += deltaTime;



            if (p.Age < Delay) {
                // Пока возраст частицы меньше некоторого времени, она движется в заданном направлении
                p.position += direction * deltaTime;
            }
            else {
                // Как только возраст частицы достигает некоторого времени, на неё начинает действовать гравитация
                p.position += gravity * deltaTime;
            }

            // Если возраст частицы превышает максимальное значение, она "умирает" и её можно перезапустить
            if (p.Age >= Lifetime) {
                p.position = direction;  // или какое-то другое начальное положение
                p.Age = 0.0f;
            }

            p.position += p.velocity * deltaTime;
            p.Age += Age * deltaTime;
            p.position += direction * deltaTime;
            p.position += gravity * deltaTime;
            p.position += wind * deltaTime;
            p.Lifetime -= deltaTime;


            if (p.Lifetime <= 0.0f) {
                p.position = glm::vec3(distribution(generator), distribution(generator), distribution(generator));
                p.position = glm::vec3(0.0f, 0.0f, 0.0f);
                p.Lifetime = Lifetime;
            }

        }


        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Particle) * particles.size(), &particles[0]);
        glBindBuffer(GL_ARRAY_BUFFER, 0);


    }

    void Draw(Shader& shader, glm::mat4 projection, glm::mat4 view) {
        glm::mat4 model = glm::mat4(10.0f);  // identity matrix

        shader.use();
        shader.setFloat("pointSize", pointSize);
        shader.setMat4("projection", projection);
        shader.setMat4("view", view);
        shader.setMat4("model", model);  // set model matrix


        glBindVertexArray(VAO);
        glDrawArrays(GL_POINTS, 0, particles.size());
        glBindVertexArray(0);


    }

    float getLifetime() const {
        return Lifetime;
    }
    void setLifetime(float newLifetime) {

        Lifetime = newLifetime;
        //  for (Particle& p : particles) {
         //     p.Lifetime = newLifetime;
         // }
    }

    glm::vec4 getColor() const {
        return color; // Предполагаем, что у вас есть член данных `color` типа glm::vec4
    }
    void setColor(const glm::vec4& newColor) {
        color = newColor;
        for (Particle& p : particles) {
            p.color = newColor;
        }
    }

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
        Age = newAge;
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
    float Lifetime = 1.0f;
    float pointSize;
    glm::vec3 spawnPosition;
    glm::vec3 direction;
    glm::vec3 gravity, wind;
    float Age;
    float Delay;
    float MaxAge;
};
