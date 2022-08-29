#include "camera.hpp"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>
camera::camera(vec3 pos, vec3 dir, vec3 up, int w, int h, float fovdeg, float n, float f)
{
	mCameraPos = pos;
	mCameraDir = dir;
	mCameraUp = up;
	wWidth = w;
	wHeight = h;
	float mFOV = fovdeg;
	float mNear = n;
	float mFar = f;
	mWAspect = (float)wWidth / wHeight;
	this->update();
}
camera::~camera()
{

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
vec3 camera::GetCamPos()
{
	return mCameraPos;
}
vec3 camera::GetCamDir()
{
	return mCameraDir;
}
vec3 camera::GetCamUp()
{
	return mCameraUp;
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
	// Makes camera look in the right direction from the right position
	mViewMatrix = glm::lookAt(mCameraPos, mCameraPos + mCameraDir, mCameraUp);
	mProjectionMatrix = glm::perspective(glm::radians(mFOV), mWAspect, mNear, mFar);
	//What is this for? Deltatime?
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}
//TODO
void camera::set_projection(float fov_deg, glm::ivec2 const& window_size, float near, float far)
{
	mFOV = glm::radians(fov_deg);
	wWidth = window_size.x;
	wHeight = window_size.y;
	mNear = near;
	mFar = far;
	mWAspect = (float)window_size.x / window_size.y;
	mProjectionMatrix = glm::perspective(glm::radians(fov_deg), mWAspect, near, far);

}
//TODO
void camera::set_position(vec3 const& pos)
{
	mCameraPos = pos;
}
//TODO
void camera::set_target(vec3 const& tgt)
{
	glm::vec3 d = tgt - mCameraPos;
	mCameraDir = glm::normalize(d);
}
///////////////////////////////////////////////////////////////////////////////
