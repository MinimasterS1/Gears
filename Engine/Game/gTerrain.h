#pragma once

#include "gActor.h"

#include <glm/gtc/type_ptr.hpp>
#include <functional>
#include <filesystem>

#include <fstream>
#include <string>

namespace terrain = std::filesystem;


class Terrain : public AActor
{

public:


	Terrain();

	void BeginPlay() override;

	void EventTick(float DeltaTime) override;

	void SpawnStaticMesh(const std::vector<terrain::path>& filePaths,
							const std::vector<glm::vec3>& Position,
							const std::vector<glm::vec3>& Scale,
							const std::vector<glm::vec3>& Rotation) override;

	
};
