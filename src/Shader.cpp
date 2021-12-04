#include "Shader.h"
#include "ResourcesFunctions.h"



Shader::Shader()
{

}

Shader::Shader(const char* vertShaderFile, const char* fragShaderFile)
{
	std::string v = getFileData(vertShaderFile);
	std::string f = getFileData(fragShaderFile);

	//For an unknown reason you have to use v and f as tmp variables otherwise the shader will not work
	//const char* vertexShaderSource = getFileData(vertShaderFile).c_str();
	//const char* fragmentShaderSource = getFileData(fragShaderFile).c_str();

	const char* vertexShaderSource = v.c_str();
	const char* fragmentShaderSource = f.c_str();

	

	// Create Vertex Shader Object and get its reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Attach Vertex Shader source to the Vertex Shader Object
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(vertexShader);

	// Create Fragment Shader Object and get its reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Attach Fragment Shader source to the Fragment Shader Object
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(fragmentShader);

	// Create Shader Program Object and get its reference
	reference = glCreateProgram();
	// Attach the Vertex and Fragment Shaders to the Shader Program
	glAttachShader(reference, vertexShader);
	glAttachShader(reference, fragmentShader);
	// Wrap-up/Link all the shaders together into the Shader Program
	glLinkProgram(reference);

	// Delete the now useless Vertex and Fragment Shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


}

void Shader::makeCurrentShader()
{
	glUseProgram(reference);
}

void Shader::terminate()
{
	glDeleteProgram(reference);	
}

void Shader::setUniform(const char* name, const glm::vec3& vec)
{
	GLint loc = glGetUniformLocation(reference,name);
	glUniform3f(loc, vec.x,vec.y,vec.z);
}
void Shader::setUniform(const char* name, const glm::vec2& vec)
{
	GLint loc = glGetUniformLocation(reference, name);
	glUniform2f(loc, vec.x, vec.y);
}
void Shader::setUniform(const char* name, const glm::vec4& vec)
{
	GLint loc = glGetUniformLocation(reference, name);
	glUniform4f(loc, vec.x, vec.y, vec.z, vec.w);
}
void Shader::setUniform(const char* name, const glm::mat2& mat)
{
	GLint loc = glGetUniformLocation(reference, name);
	glUniformMatrix2fv(loc, 1, GL_FALSE, glm::value_ptr(mat));
}
void Shader::setUniform(const char* name, const glm::mat3& mat)
{
	GLint loc = glGetUniformLocation(reference, name);
	glUniformMatrix3fv(loc,1,GL_FALSE ,glm::value_ptr(mat));
}
void Shader::setUniform(const char* name, glm::mat4& mat)
{
	//const char* test = name.c_str();
	GLint loc = glGetUniformLocation(reference, name);
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat));
	
}

