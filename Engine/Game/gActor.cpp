#include "gActor.h"
#include "Editor/gContentBrowser.h"
#include "gObject.h"
#include "bullet/btBulletDynamicsCommon.h"


ContentBrowser* StaticMesh = nullptr;

btDiscreteDynamicsWorld* dynamicsWorld;
btRigidBody* cubeRigidBody;


AActor::AActor()
{

    bool ActorInitialized = true; 

    if (ActorInitialized) {

       
        StaticMesh = new ContentBrowser();

        InitPhysics();
    }

}

void AActor::BeginPlay()
{

    const std::vector<fs::path> Paths = { "../src/Models/wood.modelbin" };

    std::vector<glm::vec3> initialPositions = { glm::vec3(0.0f, 5.0f, 0.0f) };
    std::vector<glm::vec3> initialScale = { glm::vec3(1.0f, 1.0f, 1.0f) };
    std::vector<glm::vec3> initialRotation = { glm::vec3(0.0f, 0.0f, 0.0f) };

    SpawnStaticMesh(Paths, initialPositions, initialScale, initialRotation);
}

 void AActor::EventTick(float DeltaTime)
{
     SceneObject& retrievedObject = myScene.objects[0];

     dynamicsWorld->stepSimulation(DeltaTime, 1);

     
     btTransform trans;
     cubeRigidBody->getMotionState()->getWorldTransform(trans);
     glm::vec3 newPosition(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ());
     retrievedObject.setPosition(newPosition);
     dynamicsWorld->debugDrawWorld();
     StaticMesh->UpdateObjectData();  
  
}

void AActor::SpawnStaticMesh(const std::vector<actor::path>& filePaths,
                            const std::vector<glm::vec3>& Position,
                            const std::vector<glm::vec3>& Scale,
                            const std::vector<glm::vec3>& Rotation)
 {

    StaticMesh->LoadOnScene(filePaths, Position, Scale, Rotation);
    myScene.LogSceneObjectsInfo();
    btCollisionShape* cubeShape = new btBoxShape(btVector3(1, 1, 1));

    btTransform startTransform;
    startTransform.setIdentity();
    startTransform.setOrigin(btVector3(0, 5, 0));  

    btDefaultMotionState* cubeMotionState = new btDefaultMotionState(startTransform);
    btRigidBody::btRigidBodyConstructionInfo cubeRigidBodyCI(0.5, cubeMotionState, cubeShape);
    cubeRigidBody = new btRigidBody(cubeRigidBodyCI);

    
    dynamicsWorld->addRigidBody(cubeRigidBody);

}

void AActor::InitPhysics()
{
    btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
    btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);
    btBroadphaseInterface* overlappingPairCache = new btDbvtBroadphase();
    btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver();

    dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);

    dynamicsWorld->setGravity(btVector3(0, -9.81, 0));
}



void AActor::AddActorRotation()
{
    
    SceneObject& retrievedObject = myScene.objects[0];

   float angularSpeedX = 1.0f;
   float angularSpeedY = 0.0f;
   float angularSpeedZ = 0.0f;

    
    glm::vec3 currentRotation = retrievedObject.getRotation();
    currentRotation.x += angularSpeedX * 1;
    currentRotation.y += angularSpeedY * 1;
    currentRotation.z += angularSpeedZ * 1;

   
    retrievedObject.setRotation(currentRotation);



}

void AActor::AddActorPosition()
{

    
    SceneObject& retrievedObject = myScene.objects[0];

    
    float moveSpeedX = 0.005f;
    float moveSpeedY = 0.0f;
    float moveSpeedZ = 0.0f;

   
    glm::vec3 currentPosition = retrievedObject.getPosition();
    currentPosition.x += moveSpeedX * 1;
    currentPosition.y += moveSpeedY * 1;
    currentPosition.z += moveSpeedZ * 1;

   
    retrievedObject.setPosition(currentPosition);

   
    StaticMesh->UpdateObjectData();

    

}




   

