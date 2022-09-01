#include "window.hpp"
#include "camera.hpp"
#include "glm/glm.hpp"
#include "InputManager.hpp"
constexpr unsigned window_width = 1024;
constexpr unsigned window_height = 760;
int main()
{
    window w(window_width, window_height, "cs350_framework", true);
    //camera(vec3 eye_pos, vec3 up, vec3 position_to_look_at, float FOV, float aspect, float near, float far);
    glm::vec3 camPos(0.0f, 0.0f, 0.0f);
    glm::vec3 camUp(0.0f, 1.0f, 0.0f);
    glm::vec3 camDir(0.0f, 0.0f, -1.0f);
    float FOV_Rad = glm::radians(45.0f);
    float aspect = (float)1024 / (float)760;
    float near = 0.1f;
    float far = 100.0f;
    //create a camera for the scene
    camera c(camPos, camDir, camUp, window_width, window_height, 45.0f, near, far);
    
    //Load GLAD so it configures OpenGL
    gladLoadGL();
    // Specify the viewport of OpenGL in the Window
    glViewport(0, 0, window_width, window_height);
    //set the clear color
    glClearColor(0.05f, 0.07f, 0.2f, 1.0f);

    //InputManager
    InputManager input(w.GetWindowPtr(), &c);
    //window object is in charge of glclear, swap buffers and glfwpollevents
    while (w.update()) 
    {    
        input.ReceiveInputs();
        //camera update will update V and P matrices and deltatime
        c.update();
        //Draw
        // ...
        //
    }
    return 0;
}
