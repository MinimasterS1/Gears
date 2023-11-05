#pragma once

#ifndef MODEL_H
#define MODEL_H

#include <glad/glad.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "gImage.h"
#include "assimp/Importer.hpp"
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

#include "gMesh.h"
#include "gShader.h"


using namespace std;

unsigned int TextureFromFile(const char* path, const string& directory, bool gamma = false);


class Model
{
public:

    Model() {};

    ~Model() {};

    vector<Texture> textures_loaded; 
    vector<Mesh> meshes;
    string directory;
    bool gammaCorrection;

   

    Model(string const& path, bool gamma = false) : gammaCorrection(gamma)
    {
        loadModel(path);
    }

    void Draw(Shader shader);
   
   
    void SerializeModel(const std::string& filename);

    void DeserializeModel(const std::string& filename, const std::string& directory);


    void loadModel(string const& path);
   
    void processNode(aiNode* node, const aiScene* scene);
    

    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
   
    

 vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
   

 vector<Texture> diffuseMaps;

 vector<Texture> specularMaps;

 std::vector<Texture> normalMaps;
 std::vector<Texture> heightMaps;


};

inline unsigned int TextureFromFile(const char* path, const string& directory, bool gamma)
{
    string filename = string(path);
    filename = directory + '/' + filename;
    //std::cout << "Texture at path Load model : " << directory << std::endl;
    unsigned int textureID;
    glGenTextures(1, &textureID);
    int width, height, nrComponents;
    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
       
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
       // std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
        return 0;  // Возвращаем 0, если загрузка не удалась
    }

    return textureID;
}









#endif