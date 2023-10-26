#include "gApplication.h"
#include <iostream>
#include <thread>
#include <conio.h>
#include <mutex>

#include "gVideoMg.h"
#include "gInputMg.h"
#include "gAudioMg.h"

VideoAPI gVideoManager;
Input* gInputManager = nullptr;
SoundManager gAudioManager;



EngineAPI_Manager::~EngineAPI_Manager() {}

void PlayMusic() {
    gAudioManager.Init();
 
}

void EngineAPI_Manager::RunApplication() {
    gVideoManager.startUp();
    gInputManager = new Input(camera);

    // Создайте поток для воспроизведения музыки
    std::thread musicThread(PlayMusic);

    MainLoop();

  
    musicThread.join();
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

