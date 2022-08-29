#include "InputManager.hpp"
InputManager::InputManager(GLFWwindow* window, camera* cam)
{
	mCurrentWindow = window;
	mCurrentCamera = cam;
}
InputManager::~InputManager()
{
	mCurrentWindow = NULL;
}
void InputManager::ReceiveInputs()
{
	// Handles key inputs
	if (glfwGetKey(mCurrentWindow, GLFW_KEY_W) == GLFW_PRESS)
	{
		Input_Press_W();
	}
	if (glfwGetKey(mCurrentWindow, GLFW_KEY_A) == GLFW_PRESS)
	{
		Input_Press_A();
	}
	if (glfwGetKey(mCurrentWindow, GLFW_KEY_S) == GLFW_PRESS)
	{
		Input_Press_S();
	}
	if (glfwGetKey(mCurrentWindow, GLFW_KEY_D) == GLFW_PRESS)
	{
		Input_Press_D();
	}
	if (glfwGetKey(mCurrentWindow, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		Input_Press_SPACE();
	}
	if (glfwGetKey(mCurrentWindow, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		Input_Press_LCTRL();
	}
	if (glfwGetKey(mCurrentWindow, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		Input_Press_LSHIFT();
	}
	else if (glfwGetKey(mCurrentWindow, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		Input_Release_LSHIFT();
	}
	// Handles mouse inputs
	if (glfwGetMouseButton(mCurrentWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		Input_Press_MOUSE_LEFT();
	}
	else if (glfwGetMouseButton(mCurrentWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		Input_Release_MOUST_LEFT();
	}
	if (glfwGetKey(mCurrentWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		Input_Press_ESC();
	}
}
//these inputs will do whatever the program has been set to do on said received input, in this case, they will manipulate the camera object
void InputManager::Input_Press_W()
{
	mCurrentCamera->Camera_Forward();
}
void InputManager::Input_Press_A()
{
	mCurrentCamera->Camera_Left();
}
void InputManager::Input_Press_S()
{
	mCurrentCamera->Camera_Back();
}
void InputManager::Input_Press_D()
{
	mCurrentCamera->Camera_Right();
}
void InputManager::Input_Press_SPACE()
{
	mCurrentCamera->Camera_Up();
}
void InputManager::Input_Press_LCTRL()
{
	mCurrentCamera->Camera_Down();
}
void InputManager::Input_Press_LSHIFT()
{
	mCurrentCamera->Camera_Speed_Faster();
}
void InputManager::Input_Release_LSHIFT()
{
	mCurrentCamera->Camera_Speed_Normal();
}
void InputManager::Input_Press_MOUSE_LEFT()
{
	mCurrentCamera->Camera_MouseLook(mCurrentWindow);
}
void InputManager::Input_Release_MOUST_LEFT()
{
	mCurrentCamera->Camera_Mouse_Look_Release(mCurrentWindow);
}
void InputManager::Input_Press_ESC()
{
	glfwSetWindowShouldClose(mCurrentWindow, GL_TRUE);
}