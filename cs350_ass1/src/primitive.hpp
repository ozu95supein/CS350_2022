#ifndef __PRIMITIVE_HPP__
#define __PRIMITIVE_HPP__

#include "opengl.hpp"
#include <vector>
struct DebugVertex
{
	DebugVertex(glm::vec3 p) : position(p) {}
	glm::vec3 position;
};
enum P_TYPE { E_POINT = 0, E_SEGMENT = 1, E_TRIANGLE = 2, E_PLANE = 3, E_AABB = 4, E_SPHEREDISC = 5 };
class primitive
{

public:
	primitive(P_TYPE p);	//constructor that will make primitives based on the type that is passed
	~primitive();
	void AddDebugVertex(glm::vec3 p);
	void GenerateVertexBuffers();
	void GeneratePointBuffers(GLuint& vbo, GLuint& vao);
	void TranslateVertexByIndex(unsigned int index, glm::vec3 newpos);
	GLuint GetVAO();
	GLuint GetVBO();
private:
	std::vector <DebugVertex> mVertexList;
	P_TYPE mType;
	GLuint mVBO;
	GLuint mVAO;
	float mDistance;
};
#endif // __PRIMITIVE_HPP__
