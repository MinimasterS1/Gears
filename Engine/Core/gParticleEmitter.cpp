#include "gParticleEmitter.h"

ParticleEmitter::ParticleEmitter(int numParticles)
{
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

void ParticleEmitter::Update(float deltaTime)
{

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
        if (p.Age >= lifetime) {
            p.position = direction;  // или какое-то другое начальное положение
            p.Age = 0.0f;
        }

        p.position += p.velocity * deltaTime;
        p.Age += age * deltaTime;
        p.position += direction * deltaTime;
        p.position += gravity * deltaTime;
        p.position += wind * deltaTime;
        p.Lifetime -= deltaTime;


        if (p.Lifetime <= 0.0f) {
            p.position = glm::vec3(distribution(generator), distribution(generator), distribution(generator));
            p.position = glm::vec3(0.0f, 0.0f, 0.0f);
            p.Lifetime = lifetime;
        }

    }


    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Particle) * particles.size(), &particles[0]);
    glBindBuffer(GL_ARRAY_BUFFER, 0);


}

void ParticleEmitter::Draw(Shader& shader, glm::mat4 projection, glm::mat4 view)
{
    glm::mat4 model = glm::mat4(10.0f);  

    shader.use();
    shader.setFloat("pointSize", pointSize);
    shader.setMat4("projection", projection);
    shader.setMat4("view", view);
    shader.setMat4("model", model);  


    glBindVertexArray(VAO);
    glDrawArrays(GL_POINTS, 0, particles.size());
    glBindVertexArray(0);

}

void ParticleEmitter::setColor(const glm::vec4& newColor)
{
    color = newColor;
    for (Particle& p : particles) {
        p.color = newColor;
    }
}
