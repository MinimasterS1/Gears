#include "gApplication.h"
#include <iostream>


#include "gVideoMg.h"
#include "gInputMg.h"
#include "gResources.h"




void EngineAPI_Manager::RunApplication() {
    gVideoManager.startUp();
    gInputManager = new Input(camera);

    resources.LoadLevel();
 
    MainLoop();

  
}

void EngineAPI_Manager::MainLoop() {
    while (!gVideoManager.ShouldClose()) {
       
        Update();
        Render();
    }
}

void EngineAPI_Manager::Update() {

   
    gVideoManager.update();
}

void EngineAPI_Manager::Render() {


    gVideoManager.Render();
}

void EngineAPI_Manager::ShutDownApplication() {

    gVideoManager.shutDown();
    delete gInputManager;
    gInputManager = nullptr;
}

