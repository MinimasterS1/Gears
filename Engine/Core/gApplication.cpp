#include "gApplication.h"

#include "gVideoMg.h"
#include "gInputMg.h"
#include "gAudioMg.h"



VideoAPI      gVideoManager;
Input*        gInputManager = nullptr;
SoundManager  gAudioManager;

EngineAPI_Manager::~EngineAPI_Manager()
{

}

void EngineAPI_Manager::RunApplication()
{

	gVideoManager.startUp();

	gInputManager = new Input(camera);

	
	MainLoop();
}

void EngineAPI_Manager::MainLoop()
{

	while (!gVideoManager.ShouldClose()) {

		Update();
		Render();
		
	}
}


void EngineAPI_Manager::Update()
{
	gVideoManager.update();
}

void EngineAPI_Manager::Render()
{
	gVideoManager.Render();
}

void EngineAPI_Manager::ShutDownApplication()
{
	gVideoManager.shutDown();

	gAudioManager.CleanUp();

	delete  gInputManager;
	gInputManager = nullptr;
}


