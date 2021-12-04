#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Macros.h"




enum class PrimitiveType{Circle,Rectangle,Polygon};

struct Buffers 
{
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
	int nbIndices;
};

class Primitive
{
public:
	Primitive();
	Primitive(PrimitiveType type,float* polygonVert = NULL,int nbPoints = 0);
	void drawSolid();
	void drawWireFrame();
	//int nbPoints;

private:
	Buffers wireFrameBuffers;
	Buffers solidBuffers;

};