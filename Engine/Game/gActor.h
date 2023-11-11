#pragma once
#include "Editor/gContentBrowser.h"
#include <glm/gtc/type_ptr.hpp>
#include <functional>
#include <filesystem>
#include <fstream>
#include <string>
#ifndef AACTOR_H
#define AACTOR_H

#include "bullet/btBulletDynamicsCommon.h"

namespace actor = std::filesystem;

extern ContentBrowser* StaticMesh;

class AActor
{

public:

	AActor() ;

	virtual void BeginPlay();

	virtual void EventTick(float DeltaTime);

	virtual void SpawnStaticMesh(const std::vector<actor::path>& filePaths, const std::vector<glm::vec3>& Position, const std::vector<glm::vec3>& Scale,const std::vector<glm::vec3>& Rotation);

	virtual void AddActorRotation(float AngularX, float ScaleX,float AngularY, float ScaleY, float AngularZ, float ScaleZ);

	virtual void AddActorPosition(float SpeedX, glm::vec3 PositionX, float SpeedY, glm::vec3 PositionY, float SpeedZ, glm::vec3 PositionZ);

	virtual void SetActorRotation(float X, float Y, float Z);

	virtual void SetActorPosition(float X, float Y, float Z);

	virtual void SetActorScale(float X, float Y, float Z);

	virtual void InitPhysics();

	btDiscreteDynamicsWorld* dynamicsWorld;
	btRigidBody* cubeRigidBody;

private:

	float SpeedX, SpeedY, SpeedZ;
	glm::vec3 PositionX, PositionY, PositionZ;

};

#endif