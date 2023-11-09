#pragma once


#include <glm/gtc/type_ptr.hpp>
#include <functional>
#include <filesystem>

#include <fstream>
#include <string>
#ifndef AACTOR_H
#define AACTOR_H



namespace actor = std::filesystem;


class AActor
{

public:

	AActor() ;

	virtual void BeginPlay();

	virtual void EventTick(float DeltaTime);

	virtual void SpawnStaticMesh(const std::vector<actor::path>& filePaths,
							     const std::vector<glm::vec3>& Position,
							     const std::vector<glm::vec3>& Scale,
							     const std::vector<glm::vec3>& Rotation);

	virtual void AddActorRotation();

	virtual void AddActorPosition();


private:

	void InitPhysics();


};





#endif