
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Macros.h"
#include <string>


class Shader
{
public:
	Shader();
	Shader(const char* vertShaderFile, const char* fragShaderFile);
	void makeCurrentShader();
	void terminate();
	GLuint reference;
	void setUniform(const char* name, const glm::vec3& vec);
	void setUniform(const char* name, const glm::vec2& vec);
	void setUniform(const char* name, const glm::vec4& vec);
	void setUniform(const char* name, const glm::mat2& mat);
	void setUniform(const char* name, const glm::mat3& mat);
	void setUniform(const char* name, glm::mat4& mat);

	static Shader* Shader::getDefaultShader();
	

	
	



	
	
};






