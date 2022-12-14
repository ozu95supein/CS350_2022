#include "window.hpp"
#include <iostream>
void window_size_callback(GLFWwindow* window, int width, int height);
void glfw_Error_Callback(int, const char* err_str)
{
	std::cerr << "GLFW Error: " << err_str << std::endl;
	exit(EXIT_FAILURE);
}
window::window(int w, int h, const char* window_name, bool visible)
{
	// Register error callback first
	glfwSetErrorCallback(glfw_Error_Callback);

	//Init the GLFW library and check if init is successful
	if (!glfwInit())
	{
		// Initialization failed
		//TODO PRINT OUT A GOOD ERROR CODE
		exit(EXIT_FAILURE);
	}
	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	mWindow = glfwCreateWindow(w, h, window_name, NULL, NULL);
	// Error check if the window fails to create
	if (mWindow == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		std::abort();
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(mWindow);
	//Load GLAD so it configures OpenGL
	gladLoadGL();
	//sets initial visibility
	glfwWindowHint(GLFW_VISIBLE, visible);
	glViewport(0, 0, w, h);

}
window::~window()
{
	this->destroy();
}
bool window::update()
{
	int width, height;
	glfwGetFramebufferSize(mWindow, &width, &height);
	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT);
	// Swap the back buffer with the front buffer
	glfwSwapBuffers(mWindow);
	// Take care of all GLFW events
	glfwPollEvents();
	//return whatever this 
	return !glfwWindowShouldClose(mWindow);
}
void window::destroy()
{
	// Delete window before ending the program
	glfwDestroyWindow(mWindow);
	mWindow = NULL;
	// Terminate GLFW before ending the program
	glfwTerminate();
}
void window_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
GLFWwindow* window::GetWindowPtr()
{
	return mWindow;
}