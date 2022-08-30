#ifndef __SHADER_HPP__
#define __SHADER_HPP__
#include<glad/glad.h>

class Shader
{
public:
	GLuint ID;
	Shader();
	Shader(const char * vertexSource, const char * fragmentSource);
	~Shader();
	// Activates the Shader Program
	void Activate();
	// Deletes the Shader Program
	void Delete();
	//returns the ID
	unsigned int GetShaderID();
private:
	// Checks if the different Shaders have compiled properly
	void compileErrors(unsigned int shader, const char* type);
	
};

#endif // __SHADER_HPP__
