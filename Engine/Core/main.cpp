#include "gLogger.h"


int main(int argc, const char* argv[])
{

    Logger LOG;


    LOG.Log(Logger::LogLevel::INFO, " ERROR SYSTEM DEBUG  ", 10);


    return 0;
}