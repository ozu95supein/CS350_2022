#include "camera.hpp"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>
camera::camera()
{
	mViewMatrix = mat4(1.0f);
	mProjectionMatrix = mat4(1.0f);
}
camera::~camera()
{

}
camera::camera(mat4 V, mat4 P)
{
	mViewMatrix = V;
	mProjectionMatrix = P;

}
camera::camera(vec3 eye_pos, vec3 up, vec3 position_to_look_at, float FOV, float aspect, float near, float far)
{
	mViewMatrix = lookAt(eye_pos, position_to_look_at, up);
	mProjectionMatrix = glm::perspective(FOV, aspect, near, far);
}
mat4 camera::GetViewMatrix()
{
	return mViewMatrix;
}
void camera::SetViewMatrix(mat4 v)
{
	mViewMatrix = v;
}
mat4 camera::GetProjectionMatrix()
{
	return mProjectionMatrix;
}
void camera::SetProjectionMatrix(mat4 p)
{
	mProjectionMatrix = p;
}
vec3 camera::ExtractCamPosition()
{
	vec3 result;
	result.x = mViewMatrix[0].w;
	result.y = mViewMatrix[1].w;
	result.z = mViewMatrix[2].w;
	return result;
}
vec3 camera::ExtractCamRight()
{
	vec3 result;
	result.x = mViewMatrix[0].x;
	result.y = mViewMatrix[0].y;
	result.z = mViewMatrix[0].z;
	return result;
}
vec3 camera::ExtractCamUp()
{
	vec3 result;
	result.x = mViewMatrix[1].x;
	result.y = mViewMatrix[1].y;
	result.z = mViewMatrix[1].z;
	return result;
}
vec3 camera::ExtractCamDirection()
{
	vec3 result;
	result.x = mViewMatrix[0].x;
	result.y = mViewMatrix[0].y;
	result.z = mViewMatrix[0].z;
	return result;
}

void camera::Camera_Forward()
{
	vec3 camPos = this->ExtractCamPosition();
	vec3 camDir = this->ExtractCamDirection();
	vec3 camUp = this->ExtractCamUp();
	float camspeed = speed * deltaTime;

	camPos += camspeed * camDir;
	mat4 newViewMat = lookAt(camPos, camPos+camDir, camUp);
	SetViewMatrix(newViewMat);
}
void camera::Camera_Left()
{
	vec3 camPos = this->ExtractCamPosition();
	vec3 camDir = this->ExtractCamDirection();
	vec3 camUp = this->ExtractCamUp();
	float camspeed = speed * deltaTime;

	camPos += camspeed * -glm::normalize(glm::cross(camDir, camUp));
	mat4 newViewMat = lookAt(camPos, camPos + camDir, camUp);
	SetViewMatrix(newViewMat);
}
void camera::Camera_Back()
{
	vec3 camPos = this->ExtractCamPosition();
	vec3 camDir = this->ExtractCamDirection();
	vec3 camUp = this->ExtractCamUp();
	float camspeed = speed * deltaTime;

	camPos += camspeed * -camDir;
	mat4 newViewMat = lookAt(camPos, camPos + camDir, camUp);
	SetViewMatrix(newViewMat);
}
void camera::Camera_Right()
{
	vec3 camPos = this->ExtractCamPosition();
	vec3 camDir = this->ExtractCamDirection();
	vec3 camUp = this->ExtractCamUp();
	float camspeed = speed * deltaTime;

	camPos += camspeed * glm::normalize(glm::cross(camDir, camUp));
	mat4 newViewMat = lookAt(camPos, camPos + camDir, camUp);
	SetViewMatrix(newViewMat);
}
void camera::Camera_Up()
{
	vec3 camPos = this->ExtractCamPosition();
	vec3 camDir = this->ExtractCamDirection();
	vec3 camUp = this->ExtractCamUp();
	float camspeed = speed * deltaTime;

	camPos += camspeed * camUp;
	mat4 newViewMat = lookAt(camPos, camPos + camDir, camUp);
	SetViewMatrix(newViewMat);
}
void camera::Camera_Down()
{
	vec3 camPos = this->ExtractCamPosition();
	vec3 camDir = this->ExtractCamDirection();
	vec3 camUp = this->ExtractCamUp();
	float camspeed = speed * deltaTime;

	camPos += camspeed * -camUp;
	mat4 newViewMat = lookAt(camPos, camPos + camDir, camUp);
	SetViewMatrix(newViewMat);
}
void camera::Camera_Speed_Faster()
{
	speed = FastSpeed;
}
void camera::Camera_Speed_Normal()
{
	speed = NormalSpeed;
}
void camera::Camera_MouseLook(GLFWwindow* window)
{
	// Hides mouse cursor
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	//get window width and height for calculations
	int width = 0, height = 0;
	glfwGetWindowSize(window, &width, &height);
	vec3 camPos = this->ExtractCamPosition();
	vec3 camDir = this->ExtractCamDirection();
	vec3 camUp = this->ExtractCamUp();
	
	vec3 Orientation;
	// Prevents camera from jumping on the first click
	if (firstClick)
	{
		glfwSetCursorPos(window, (width / 2), (height / 2));
		firstClick = false;
	}

	// Stores the coordinates of the cursor
	double mouseX;
	double mouseY;
	// Fetches the coordinates of the cursor
	glfwGetCursorPos(window, &mouseX, &mouseY);

	// Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
	// and then "transforms" them into degrees 
	float rotX = sensitivity * deltaTime * (float)(mouseY - (height / 2)) / height;
	float rotY = sensitivity * deltaTime * (float)(mouseX - (width / 2)) / width;

	// Calculates upcoming vertical change in the Orientation
	vec3 verticalOrientation = glm::rotate(camDir, glm::radians(-rotX), glm::normalize(glm::cross(camDir, camUp)));

	// Decides whether or not the next vertical Orientation is legal or not
	if (abs(glm::angle(verticalOrientation, camUp) - glm::radians(90.0f)) <= glm::radians(85.0f))
	{
		Orientation = verticalOrientation;
	}

	// Rotates the Orientation left and right
	Orientation = glm::rotate(Orientation, glm::radians(-rotY), camUp);

	//Make a new view matrix with this new Orientation
	mViewMatrix = lookAt(camPos, camPos + Orientation, camUp);

	// Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
	glfwSetCursorPos(window, (width / 2), (height / 2));
}
void camera::Camera_Mouse_Look_Release(GLFWwindow* window)
{
	// Unhides cursor since camera is not looking around anymore
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	// Makes sure the next time the camera looks around it doesn't jump
	firstClick = true;
}
///////////////////////////////////////////////////////////////////////////////
//TODO
void camera::update()
{
	//What is this for? Deltatime?
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

}
//TODO
void camera::set_projection(float fov_deg, glm::ivec2 const& window_size, float near, float far)
{
	mProjectionMatrix = glm::perspective(glm::radians(fov_deg), (float)window_size.x / window_size.y, near, far);
}
//TODO
void camera::set_position(vec3 const& pos)
{
	vec3 camDir = this->ExtractCamDirection();
	vec3 camUp = this->ExtractCamUp();

	mat4 newViewMat = lookAt(pos, pos + camDir, camUp);
	SetViewMatrix(newViewMat);
}
//TODO
void camera::set_target(vec3 const& tgt)
{
	vec3 camPos = this->ExtractCamPosition();
	vec3 camDir = this->ExtractCamDirection();
	vec3 camUp = this->ExtractCamUp();

	vec3 newDir = tgt - camPos;
	mat4 newViewMat = lookAt(camPos, camPos + newDir, camUp);
	SetViewMatrix(newViewMat);
}
///////////////////////////////////////////////////////////////////////////////
