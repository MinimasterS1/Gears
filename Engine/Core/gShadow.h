#pragma once
#include "gShader.h"
#include "gMesh.h"

class Shadow {
public:
    Shadow();
    ~Shadow();

    void Initialize(int width, int height);
    void StartRenderPass();
    void EndRenderPass();
    void RenderShadowMap(Shader& depthShader, const std::vector<Mesh>& meshes, const glm::mat4& lightSpaceMatrix);
    void SetLightSpaceMatrix(const glm::mat4& lightSpaceMatrix);

    // Другие методы и члены класса, если необходимо
};