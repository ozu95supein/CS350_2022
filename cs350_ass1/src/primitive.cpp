#include "primitive.hpp"

primitive::primitive(P_TYPE p)	//constructor that will make primitives based on the type that is passed
{
	mType = p;
	//initialize everything to 0;
	mVBO = 0;
	mVAO = 0;
	mDistance = 0;
	mVertexList.clear();
}
primitive::~primitive()
{
	// Delete the VBOs
	glDeleteBuffers(1, &mVBO);
	// Delete the VAO
	glDeleteVertexArrays(1, &mVAO);
	mVBO = 0;
	mVAO = 0;
	mVertexList.clear();
}
void primitive::AddDebugVertex(glm::vec3 p)
{
	DebugVertex v(p);
	mVertexList.push_back(v);
}
void primitive::TranslateVertexByIndex(unsigned int index, glm::vec3 newpos)
{
	glm::vec3* v = &(mVertexList[index].position);
	*v = newpos;
}
void primitive::GenerateVertexBuffers()
{
	GeneratePointBuffers(mVBO, mVAO);	//no reason not to do it this way as well
}
void primitive::GeneratePointBuffers(GLuint& vbo, GLuint& vao)
{	   
	unsigned long stride = sizeof(DebugVertex);

	// create buffer for VAO
	glGenVertexArrays(1, &vao);
	// create buffer for VBO
	glGenBuffers(1, &vbo);
	//bind so we are now doing stuff to the vao
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, (sizeof(DebugVertex)), (const void*)&(*(mVertexList.begin())), GL_STATIC_DRAW);
	//positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, 0);
	// Unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

GLuint primitive::GetVAO()
{
	return mVAO;
}
GLuint primitive::GetVBO()
{
	return mVBO;
}