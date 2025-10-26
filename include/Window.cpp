#include <Window.h>
#include <Camera.h>


Window::Window(unsigned int width = 1280, unsigned int height = 720)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	
	window = glfwCreateWindow(width, height, "GLSL Suite", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		windowCreation = -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, 
		[](GLFWwindow* window, int width, int  height)
		{
			glViewport(0, 0, width, height);
		});
	
	//glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "failed to initialize GLAD" << std::endl;
		gladLoad = -1;
	}

}
Window::~Window() { glfwTerminate(); }

GLFWwindow* Window::getWindow() const
{
	return window;
}



int Window::getWindowCreationSuccess()
{
	return this->windowCreation;
}

int Window::getGLADSuccess()
{
	return this->gladLoad;
}

unsigned int Window::getWidth()
{
	return this->width;
}

unsigned int Window::getHeight()
{
	return this->height;
}


