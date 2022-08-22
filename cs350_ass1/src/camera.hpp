#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__

#include "math.hpp"
#include "opengl.hpp"
class GLFWWindow;

class camera
{
public:
	float deltaTime = 0.0f;	// Time between current frame and last frame
	float lastFrame = 0.0f; // Time of last frame

    //my functions
    camera();
    ~camera();
    camera(mat4 V, mat4 P);
    camera(vec3 eye_pos, vec3 up, vec3 position_to_look_at, float FOV, float aspect, float near, float far);
	mat4 GetViewMatrix();
	void SetViewMatrix(mat4 v);
	mat4 GetProjectionMatrix();
	void SetProjectionMatrix(mat4 p);
	vec3 ExtractCamPosition();
	vec3 ExtractCamRight();
	vec3 ExtractCamUp();
    vec3 ExtractCamDirection();
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

	//Variables to control the speed and smooth control of the camera
	// Prevents the camera from jumping around when first clicking left click
	bool firstClick = true;
	// Adjust the speed of the camera and it's sensitivity when looking around
	float speed = 0.01f;
	float NormalSpeed = 0.01f;
	float FastSpeed = 0.04f;
	float sensitivity = 100.0f;
};

#endif // __CAMERA_HPP__
