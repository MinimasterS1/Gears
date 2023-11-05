#pragma once


class AActor
{
public:


	AActor() {};

	virtual void BeginPlay();

	virtual void EventTick(float DeltaTime);

	virtual void EndPlay();

	
  
	float deltaTime;

};
