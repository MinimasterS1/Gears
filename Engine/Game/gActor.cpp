#include "gActor.h"
#include "Core/gCommon.h"




void AActor::BeginPlay()
{
	camera.SetPosition(5.0f, 5.1f, 0.0f);
	camera.updateCameraVectors();

}

void AActor::EventTick(float DeltaTime)
{
   
}


void AActor::EndPlay()
{

}


