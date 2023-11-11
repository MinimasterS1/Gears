#include "gVideoMg.h"
#include "gTemplate.h"
#include "gObject.h"
#include "Game/gActor.h"
#include "Game/gTerrain.h"



AActor Actor;


float VideoAPI::FPS = 0.0f;
float VideoAPI::DeltaTime = 0.0f;
float VideoAPI::LastFrame = 0.0f;
float lastX = VideoAPI::SCR_WIDTH / 2.0f;
float lastY = VideoAPI::SCR_HEIGHT / 2.0f;
bool firstMouse = true;


void VideoAPI::startUp()
{
	//LOG.Log(Logger::LogLevel::INFO, "VideoManagerStart", NULL);
	CreateWindow();

    EditorUI.reset(new EditorAPI(window, "editor"));
}

void VideoAPI::shutDown()
{
	//LOG.Log(Logger::LogLevel::INFO, "VideoManagerShutDown", NULL);

    glfwMakeContextCurrent(window);
    glfwDestroyWindow(window);
	glfwTerminate();
}

void VideoAPI::update()
{

	glfwPollEvents();
	
}

void VideoAPI::CreateWindow()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    MonitorScale(&SCR_WIDTH, &SCR_HEIGHT);

    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Engine", NULL, NULL);
    if (window == NULL)
    {
       LOG.Log(Logger::LogLevel::ERROR, "Failed to create GLFW window", NULL);

        glfwTerminate();
        return;
    }

    glfwSetWindowPos(window, 0, 25);

    glfwSetWindowUserPointer(window, this);
    glfwMakeContextCurrent(window);

    InputManager = new Input(camera);

    InputManager->startUp();

  
    glfwSetCharCallback(window, [](GLFWwindow* window, unsigned int codepoint) {
        auto w = (VideoAPI*)glfwGetWindowUserPointer(window); if (w->on_char) w->on_char(codepoint);
        });

    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int, int action, int mods) {
        auto w = (VideoAPI*)glfwGetWindowUserPointer(window); if (w->on_key) w->on_key(key, action, mods);
        });

    glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
        auto w = (VideoAPI*)glfwGetWindowUserPointer(window); if (w->on_mouse_button) w->on_mouse_button(button, action, mods);
        });

    glfwSetDropCallback(window, [](GLFWwindow* window, int numFiles, const char** paths) {
        auto w = (VideoAPI*)glfwGetWindowUserPointer(window); if (w->on_drop) w->on_drop(numFiles, paths);
        });

    glfwSetWindowUserPointer(window, this);

    glfwSetCursorPosCallback(window, [](GLFWwindow* window, double x, double y) {
        static_cast<VideoAPI*>(glfwGetWindowUserPointer(window))->InputManager->MouseCallback(window, x, y);
        });

    glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset) {
        static_cast<VideoAPI*>(glfwGetWindowUserPointer(window))->InputManager->ScrollCallback(window, xoffset, yoffset);
        });

    glfwSetFramebufferSizeCallback(window, VideoAPI::framebuffer_size_callback_static);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        LOG.Log(Logger::LogLevel::ERROR, "Failed to initialize GLAD", NULL);

        return;
    }

  
    Actor.BeginPlay();
  

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_PROGRAM_POINT_SIZE);

    glEnable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_CULL_FACE);

    glCullFace(GL_FRONT);

    glFrontFace(GL_CW);
  

    return;

 
}


bool fileExists(const std::string& filename)
{
    std::ifstream file(filename);
    return file.good();
}

void VideoAPI::Render()
{

    float currentFrame = glfwGetTime();
    DeltaTime = currentFrame - LastFrame;
    LastFrame = currentFrame;
    FPS = 1.0f / DeltaTime;
    Actor.EventTick(currentFrame);
  
    InputManager->update(window, DeltaTime);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glClearColor(0.5f, 0.5f, 0.5f, 0.0f);

    Scene& scene = Scene::Instance();


   
  
    for (SceneObject& object : scene.objects) {
        if (!object.hasMeshes()) {

           
        }
        else {
            object.Draw(camera, SCR_WIDTH, SCR_HEIGHT);

            
            glm::vec3 position = object.getPosition();
            std::stringstream ss;
            // ss << "Object Position: (" << position.x << ", " << position.y << ", " << position.z << ")";
             // logger.Log(FT_Logger::LogLevel::INFO, "SC");
        }
    }


     
 
   

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); 
    
    camera.CameraMode = true;

   static bool beginPlayExecuted = false; 

    if (EditorMode)
    {
        EditorUI->RenderEditor();
        camera.CameraMode = false;

        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
    else
    {
        if (!beginPlayExecuted)
        {
        
            beginPlayExecuted = true; 
        }
    }

 

   

    glfwSwapBuffers(window);
}

void VideoAPI::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
   
	glViewport(0, 0, width, height);
    
}

void VideoAPI::GL_Check(const char* label)
{
    {
        GLenum err;
        while ((err = glGetError()) != GL_NO_ERROR) {
            const char* errorStr;
            switch (err) {
            case GL_INVALID_ENUM: errorStr = "GL_INVALID_ENUM"; break;
            case GL_INVALID_VALUE: errorStr = "GL_INVALID_VALUE"; break;
            case GL_INVALID_OPERATION: errorStr = "GL_INVALID_OPERATION"; break;
            case GL_OUT_OF_MEMORY: errorStr = "GL_OUT_OF_MEMORY"; break;
            default: errorStr = "Unknown Error"; break;
            }

            double errorDouble = static_cast<double>(err);

            std::string errorMessage = "OpenGL Error [" + std::string(label) + "]: " + errorStr;

            LOG.Log(Logger::LogLevel::ERROR, errorMessage, errorDouble);
            std::cerr << errorMessage << std::endl;
        }
    }
}

