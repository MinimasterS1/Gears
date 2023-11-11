#include "gPhysicsWorld.h"

PhysicsWorld::PhysicsWorld() : dynamicsWorld(nullptr) {}

PhysicsWorld::~PhysicsWorld() {
    delete dynamicsWorld;
}

void PhysicsWorld::Init() {\

    btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
    btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);
    btBroadphaseInterface* overlappingPairCache = new btDbvtBroadphase();
    btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver();

    dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);

    dynamicsWorld->setGravity(btVector3(0, -9.81, 0));
}

void PhysicsWorld::Update(float deltaTime) {
    dynamicsWorld->stepSimulation(deltaTime, 1);
}