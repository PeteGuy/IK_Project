



#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>
#include "Shader.h"
#include "RigidBody.h"
#include "Primitive.h"
#include "Macros.h"
#include "Primitive.h"


namespace Render
{
	extern real windowWidth;
	extern real windowHeight;
	extern Shader defaultShader;
	extern glm::mat4 projection;
	extern std::vector<std::unique_ptr<Primitive>> primitives;
	//Default shader

	extern GLFWwindow* renderWindow;

	void initialize();
	void terminate();
	void changeWindowSize(real width, real height);

	void renderBody(RigidBody* body);
	//Render function that uses interpolation not in use for now
	void renderBody(real alpha);
	void drawPrimitive(Primitive* primitive,glm::vec2 position = glm::vec2(),float angle = 0,float xScale = 1, float yScale = 1);

	void setNewMouseButtonCallBack(GLFWmousebuttonfun callback);
	
}



