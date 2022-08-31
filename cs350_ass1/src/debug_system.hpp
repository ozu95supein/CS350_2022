#ifndef __DEBUG_SYSTEM_HPP__
#define __DEBUG_SYSTEM_HPP__
#include "camera.hpp"
#include "shader.hpp"
//point
// Nothing to do here, its a vec3
const float DebugPointSize = 10.0f;
//segment
struct Segment
{
    Segment()
    {
        start = vec3(0.0f, 0.0f, 0.0f);
        end = vec3(1.0f, 1.0f, 1.0f);
    }
    Segment(vec3 s, vec3 e)
    {
        start = s;
        end = e;
    }
    vec3 start;
    vec3 end;
};
//triangles
struct Triangle
{
    Triangle()
    {
        a = vec3(1.0f, 0.0f, 0.0f);
        b = vec3(0.0f, 1.0f, 0.0f);
        c = vec3(0.0f, 0.0f, 1.0f);
    }
    Triangle(vec3 p1, vec3 p2, vec3 p3)
    {
        a = p1;
        b = p2;
        c = p3;
    }
    vec3 a;
    vec3 b;
    vec3 c;
};
struct Plane
{
    Plane()
    {
        n = vec3(1.0f, 1.0f, 1.0f);
        d = 0;
    }
    Plane(vec3 n1, float d1)
    {
        n = n1;
        d = d1;
    }
    Plane(vec3 a, vec3 b, vec3 c)
    {
        Plane r = ComputePlane(a, b, c);
        n = r.n;
        d = r.d;
    }
    Plane ComputePlane(vec3 a, vec3 b, vec3 c)
    {
        Plane p;
        p.n = glm::normalize(glm::cross(b - a, c - a));
        p.d = glm::dot(p.n, a);
        return p;
    }
    vec3 n;		//plane normal that satisfies DOT(n, x) = d
    float d;	// d = DOT(n, p) for any given point P on a plane
};

struct AABB_C_R     //center and vector of radii representation
{
    AABB_C_R()
    {
        c = vec3(0.0f, 0.0f, 0.0f);
        r = vec3(1.0f, 1.0f, 1.0f);
    }
    AABB_C_R(vec3 cv, vec3 rv)
    {
        c = cv;
        r = rv;
    }
    vec3 c;         //center of the AABB
    vec3 r;         //radi of all sides, rx, ry, rz
};
//sphere 
struct Sphere
{
    Sphere()
    {
        c = vec3(0.0f, 0.0f, 0.0f);
        r = 1.0f;
    }
    Sphere(vec3 cv, float rf)
    {
        c = cv;
        r = rf;
    }
    vec3 c;     //center of sphere
    float r;    //radius of sphere
};
class debug_system
{
  public:
    debug_system(camera const* c);

    void draw_point(vec3 pt, vec4 color);
    void draw_segment(vec3 s, vec3 e, vec4 color);
    void draw_triangle(vec3 a, vec3 b, vec3 c, vec4 color);
    void draw_aabb(vec3 c, vec3 size, vec4 color);
    void draw_plane(vec3 pt, vec3 n, float scale, vec4 color);
    void draw_sphere(vec3 c, float r, glm::vec4 color);
    void draw_frustum_lines(mat4 const& vp, vec4 color);
    //primitives
    vec3        mDefaultPointPrim = vec3(0.0f, 0.0f, 0.0f);
    Segment     mDefaultSegmentPrim;
    Triangle    mDefaultTrianglePrim;
    Plane       mDefaultPlanePrim;
    AABB_C_R    mDefaultAABBPrim;
    Sphere      mDefaultSpherePrim;
private:
    camera const* mCam;
    Shader mDebugShader;
    
    //Buffer Objects
    GLuint mPointVAO;
    GLuint mPointVBO;
    GLuint mSegmentVAO;
    GLuint mSegmentVBO;
    GLuint mTriangleVAO;
    GLuint mTriangleVBO;
    GLuint mAABBVAO;
    GLuint mAABBVBO;
    GLuint mPlaneVAO;
    GLuint mPlaneVBO;
    GLuint mSphereVAO;
    GLuint mSphereVBO;
    GLuint mFrustrumVAO;
    GLuint mFrustrumVBO;
    //functions to initialize point buffers
    void InitPointBuffer();
};

#endif // __DEBUG_SYSTEM_HPP__
