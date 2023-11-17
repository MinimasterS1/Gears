#pragma once

#ifndef MESH_H
#define MESH_H

#include <glad/glad.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "gShader.h"

#include <string>
#include <vector>

using namespace std;

struct Vertex {

    glm::vec3 Position;

    glm::vec3 Normal;

    glm::vec2 TexCoords;

    glm::vec3 Tangent;

    glm::vec3 Bitangent;
};


struct Texture {
    unsigned int id;
    string type;
    string path;
    std::vector<unsigned char> data;
};

class Mesh {

public:

    Mesh() { };

    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;
    unsigned int VAO;

    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures)
    {
        this->vertices = vertices;
        this->indices = indices;
        this->textures = textures;
        setupMesh();
    }

    ~Mesh();

    void Initialize(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
   

    void Draw(Shader& shader);
   
   
    void setupMesh();
    

};

#endif