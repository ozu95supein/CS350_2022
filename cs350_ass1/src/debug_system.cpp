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
debug_system::debug_system(camera const*)
{

}
//TODO
void debug_system::draw_point(vec3 pt, vec4 color)
{

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