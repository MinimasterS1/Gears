#include  "gTerrain.h"



Terrain::Terrain()
{

}


void Terrain::BeginPlay()
{
    const std::vector<terrain::path> Paths = { "../src/Models/wood.modelbin" };

    std::vector<glm::vec3> initialPositions = { glm::vec3(0.0f, 5.0f, 0.0f) };
    std::vector<glm::vec3> initialScale = { glm::vec3(1.0f, 1.0f, 1.0f) };
    std::vector<glm::vec3> initialRotation = { glm::vec3(0.0f, 0.0f, 0.0f) };

    SpawnStaticMesh(Paths, initialPositions, initialScale, initialRotation);
}

void Terrain::EventTick(float DeltaTime)
{

}

void Terrain::SpawnStaticMesh(const std::vector<actor::path>& filePaths, const std::vector<glm::vec3>& Position, const std::vector<glm::vec3>& Scale, const std::vector<glm::vec3>& Rotation)
{

  
}

