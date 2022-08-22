#ifndef __WINDOW_HPP__
#define __WINDOW_HPP__

#include "opengl.hpp"

class window
{
  private:
      GLFWwindow* mWindow;
  public:
    window(int w, int h, const char* window_name, bool visible);
    ~window();
    bool update();
    void destroy();
    GLFWwindow* GetWindowPtr();
};

#endif // __WINDOW_HPP__
