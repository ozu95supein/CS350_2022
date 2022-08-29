#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__

#include "math.hpp"
#include "opengl.hpp"
class GLFWWindow;
const float DEFAULT_speed = 0.01f;
const float DEFAULT_NormalSpeed = 0.01f;
const float DEFAULT_FastSpeed = 0.04f;
const float DEFAULT_sensitivity = 100.0f;
class camera
{
public:
	float deltaTime = 0.0f;	// Time between current frame and last frame
	float lastFrame = 0.0f; // Time of last frame

    //my functions
	camera(vec3 pos, vec3 dir, vec3 up, int w, int h, float fovdeg, float n, float f);
    ~camera();
	mat4 GetViewMatrix();
	void SetViewMatrix(mat4 v);
	mat4 GetProjectionMatrix();
	void SetProjectionMatrix(mat4 p);

	vec3 ExtractCamPosition();
	vec3 ExtractCamRight();
	vec3 ExtractCamUp();
    vec3 ExtractCamDirection();
	vec3 GetCamPos();
	vec3 GetCamDir();
	vec3 GetCamUp();

	//Camera Control Functions to be externally called from the inputmanager object
	void Camera_Forward();
	void Camera_Left();
	void Camera_Back();
	void Camera_Right();
	void Camera_Up();
	void Camera_Down();
	void Camera_Speed_Faster();
	void Camera_Speed_Normal();
	void Camera_MouseLook(GLFWwindow* window);
	void Camera_Mouse_Look_Release(GLFWwindow* window);

    //external TODO functions for the demo
    void update();
    void set_projection(float fov_deg, glm::ivec2 const& window_size, float near, float far);
    void set_position(vec3 const&);
    void set_target(vec3 const&);
private:
	//matrices for the rendering of the scene
    mat4 mViewMatrix;
    mat4 mProjectionMatrix;
	//variables to determine the camera attributes
	vec3 mCameraPos;
	vec3 mCameraDir;
	vec3 mCameraUp;
	int wWidth;
	int wHeight;
	float mWAspect;
	float mFOV;
	float mNear;
	float mFar;
	//Variables to control the speed and smooth control of the camera
	// Prevents the camera from jumping around when first clicking left click
	bool firstClick = true;
	// Adjust the speed of the camera and it's sensitivity when looking around
	float speed = DEFAULT_speed;
	float NormalSpeed = DEFAULT_NormalSpeed;
	float FastSpeed = DEFAULT_FastSpeed;
	float sensitivity = DEFAULT_sensitivity;
};

#endif // __CAMERA_HPP__
