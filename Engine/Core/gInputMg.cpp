#include "gInputMg.h"


Input::Input(Camera& cam) : camera(cam), FirstMouse(true) 

{
    // Инициализируйте массив previousKeyState
    for (int i = 0; i <= GLFW_KEY_LAST; i++) {
        previousKeyState[i] = GLFW_RELEASE;
    }
}

Input::~Input() {}

void Input::startUp() {

    LOG.Log(Logger::LogLevel::INFO, "InputManager Start", NULL);
    
  

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


void Input::ProcessSingleKeyPress(GLFWwindow* window, int key, int action) {
    if (key == GLFW_KEY_Q) {
       if (action == GLFW_PRESS && !keyQPressed) {

         

        }
        else if (action == GLFW_RELEASE) {
            // Код, который нужно выполнить при отпускании кнопки Q
           //sound.StopMusic();
            keyQPressed = false;
        }
    }
    previousKeyState[key] = action;
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

  //  ProcessSingleKeyPress(window, GLFW_KEY_Q, glfwGetKey(window, GLFW_KEY_Q));
    //ProcessSingleKeyPress(window, GLFW_KEY_P, glfwGetKey(window, GLFW_KEY_P));

  

}