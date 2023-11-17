#pragma once

#ifndef EngineAPI_H
#define EngineAPI_H


#include "gVideoMg.h"
#include "gInputMg.h"
#include "gResources.h"


class EngineAPI_Manager
{
public:

    static EngineAPI_Manager& GetInstance()
    {
        static EngineAPI_Manager instance; // Создается только один раз
        return instance;
    }

    VideoAPI gVideoManager;
    Input* gInputManager = nullptr;
    Resources resources;


 

  
    void RunApplication();

    void MainLoop();
   
    void Update();
  
    void Render();

    void ShutDownApplication();

private:

    EngineAPI_Manager(const EngineAPI_Manager&) = delete;
    EngineAPI_Manager& operator=(const EngineAPI_Manager&) = delete;

    EngineAPI_Manager()
    {
        // Конструктор остается без изменений
    }

    ~EngineAPI_Manager()
    {
        // Деструктор остается без изменений
    }
   

};


#endif 