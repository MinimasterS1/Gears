#pragma once

#include "gLogger.h"
#include "gCamera.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Game/gActor.h"

extern Logger LOG;

extern Camera camera;

extern  GLFWwindow* window;

extern AActor actor;

// colsole

extern bool EditorMode;
extern bool GameConsole;
