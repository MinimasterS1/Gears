#include "gApplication.h"

EngineAPI_Manager& engine = EngineAPI_Manager::GetInstance();


int main(int argc, const char* argv[])
{
    

    engine.RunApplication();
    

 
    return 0;
}