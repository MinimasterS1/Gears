#include "gInputMg.h"

#include "gAudioMg.h"

SoundManager Sound;


Input::Input(Camera& cam) : camera(cam), FirstMouse(true) 

{
   
}

Input::~Input() {}

void Input::startUp() {
    LOG.Log(Logger::LogLevel::INFO, "InputManager Start", NULL);

    
    Sound.LoadSound("Content/Audio/01.ogg", "MySound");
}

void Input::shutDown() {

    LOG.Log(Logger::LogLevel::INFO, "InputManager ShutDown", NULL);
}

void Input::update(GLFWwindow* window, float deltaTime) {

    ProcessInput(window, deltaTime);
}

void Input::MouseCallback(GLFWwindow* window, double xpos, double ypos) 

{
    if (FirstMouse) {
        Last_X = xpos;
        Last_Y = ypos;
        FirstMouse = false;
    }

    float xoffset = xpos - Last_X;
    float yoffset = Last_Y - ypos;

    Last_X = xpos;
    Last_Y = ypos;

    // camera.ProcessMouseMovement(xoffset, yoffset);


    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);

}

void Input::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset) 
{

   
}

void Input::ProcessInput(GLFWwindow* window, float deltaTime) 
{

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
      
    

    }

    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
    {

        Sound.PlaySound("MySound");
    }
       



   
   
  
  

}