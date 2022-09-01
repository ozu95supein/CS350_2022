#include "debug_system.hpp"

namespace DebugShader{
    char const* c_vertex_shader = R"(
#version 440 core
layout(location = 0) in vec3 attr_position;
layout(location = 0) uniform mat4 uniform_mvp;
void main()
{
    vec4 vertex = vec4(attr_position, 1.0f);
    gl_Position = uniform_mvp * vertex;
}
)";

    char const* c_fragment_shader = R"(
#version 440 core
out vec4 out_color;
layout(location = 1) uniform vec4 uniform_color;
void main()
{
    out_color = uniform_color;
}
)";
}

//TODO
debug_system::debug_system(camera const* c)
{
    //create the default shader with the 
    mDebugShader = Shader(DebugShader::c_vertex_shader, DebugShader::c_fragment_shader);
    //set the camera pointer
    mCam = c;
    //primitaves are made by default as public variables
    //now we create the vaos and vbos
    //lets create the point first
    InitPointBuffer();
}
void debug_system::InitPointBuffer()
{
    // create buffer for VAO
    glGenVertexArrays(1, &mPointVAO);
    // create buffer for VBO
    glGenBuffers(1, &mPointVBO);

    //bind so we are now doing stuff to the vao
    glBindVertexArray(mPointVAO);
    glBindBuffer(GL_ARRAY_BUFFER, mPointVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec3), &mDefaultPointPrim, GL_STATIC_DRAW);
    //specify the location of 
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    
}
//TODO
void debug_system::draw_point(vec3 pt, vec4 color)
{
    // Bind the glsl program and this object's VAO
    mDebugShader.Activate();
    // Enable front-face culling
    glCullFace(GL_FRONT);
    //specify point size
    glPointSize(DebugPointSize);

    //find the location of the inputs
    GLuint loc_attr_position = glGetUniformLocation(mDebugShader.ID, "attr_position");
    GLuint loc_uniform_mvp = glGetUniformLocation(mDebugShader.ID, "uniform_mvp");

    //make the translation matrix out of the pt variable given
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::translate(trans, pt);
    //scale is determined by glPointSize, and there is no rotation or Model matrix for a point
    //now we get view and projection matrices
    mat4 V = mCam->mViewMatrix;
    mat4 P = mCam->mProjectionMatrix;
    mat4 MVP = P * V * trans;

    glBindVertexArray(mPointVAO);
    glDrawArrays(GL_POINT, 0, 1);
}
//TODO
void debug_system::draw_segment(vec3 s, vec3 e, vec4 color)
{

}
//TODO
void debug_system::draw_triangle(vec3 a, vec3 b, vec3 c, vec4 color)
{

}
//TODO
void debug_system::draw_aabb(vec3 c, vec3 size, vec4 color)
{

}
//TODO
void debug_system::draw_plane(vec3 pt, vec3 n, float scale, vec4 color)
{

}
//TODO
void debug_system::draw_sphere(vec3 c, float r, glm::vec4 color)
{

}
//TODO
void debug_system::draw_frustum_lines(mat4 const& vp, vec4 color)
{

}