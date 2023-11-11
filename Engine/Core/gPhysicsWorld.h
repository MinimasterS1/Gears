#pragma once

#ifndef PhysicsWorld_H
#define PhysicsWorld_H

#include "bullet/btBulletDynamicsCommon.h"

class PhysicsWorld {
public:
    PhysicsWorld();
    ~PhysicsWorld();

    void Init();
    void Update(float deltaTime);

    btDiscreteDynamicsWorld* GetDynamicsWorld() { return dynamicsWorld; }

private:
    btDiscreteDynamicsWorld* dynamicsWorld;
};

#endif
