#include "gVideoMg.h"
#include "gTemplate.h"

float VideoAPI::FPS = 0.0f;
float VideoAPI::DeltaTime = 0.0f;
float VideoAPI::LastFrame = 0.0f;
float lastX = VideoAPI::SCR_WIDTH / 2.0f;
float lastY = VideoAPI::SCR_HEIGHT / 2.0f;
bool firstMouse = true;


void VideoAPI::startUp()
{
	LOG.Log(Logger::LogLevel::INFO, "VideoManagerStart", NULL);
	CreateWindow();

    EditorUI.reset(new EditorAPI(window, "editor"));
}

void VideoAPI::shutDown()
{
	LOG.Log(Logger::LogLevel::INFO, "VideoManagerShutDown", NULL);

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


    glEnable(GL_DEPTH_TEST);

    glEnable(GL_PROGRAM_POINT_SIZE);

    glEnable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

   

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

    InputManager->update(window, DeltaTime);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glClearColor(0.5f, 0.5f, 0.5f, 0.0f);


    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    EditorUI->RenderEditor();

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

