#pragma once
#pragma once

#ifndef EngineAPI_H
#define EngineAPI_H





class EngineAPI_Manager
{
public:

 

    EngineAPI_Manager()
    {

    }

    ~EngineAPI_Manager();

  
    void RunApplication();

    void MainLoop();
   
    void Update();
  
    void Render();

    void ShutDownApplication();


       
   

};


#endif 