#pragma once


#ifndef PARTICLE_H
#define PARTICLE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Particle  {


public:

    glm::vec3 position;
    glm::vec4 color;
    glm::vec3 velocity;
    float Lifetime;
    float Age;


    Particle() : position(0.0f), velocity(0.0f), color(1.0f), Lifetime(0.0f) {}





};

#endif