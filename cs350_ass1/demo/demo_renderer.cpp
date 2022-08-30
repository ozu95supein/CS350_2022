#include "window.hpp"
#include "camera.hpp"
#include "glm/glm.hpp"
#include "InputManager.hpp"
int main()
{
    window w(1024,760, "cs350_framework", true);
    //camera(vec3 eye_pos, vec3 up, vec3 position_to_look_at, float FOV, float aspect, float near, float far);
    glm::vec3 camPos(0.0f, 0.0f, 0.0f);
    glm::vec3 camUp(0.0f, 1.0f, 0.0f);
    glm::vec3 camDir(0.0f, 0.0f, -1.0f);
    float FOV_Rad = glm::radians(45.0f);
    float aspect = (float)1024 / (float)760;
    float near = 0.1f;
    float far = 100.0f;
    //create a camera for the scene
    camera c(camPos, camDir, camUp, 1024, 760, 45.0f, near, far);
    
    //Load GLAD so it configures OpenGL
    gladLoadGL();
    // Specify the viewport of OpenGL in the Window
    glViewport(0, 0, 1024, 760);
    // Enables the Depth Buffer
    glEnable(GL_DEPTH_TEST);
    //set the clear color
    glClearColor(0.05f, 0.07f, 0.2f, 1.0f);

    //InputManager
    InputManager input(w.GetWindowPtr(), &c);

    while (w.update()) 
    {    
        input.ReceiveInputs();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        c.update();

    }
    return 0;
}
