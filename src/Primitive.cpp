#include "Primitive.h"

std::vector<GLuint> triangulate(const std::vector<glm::vec2>& points);


Primitive::Primitive()
{

}
Primitive::Primitive(PrimitiveType type, float* polygonVert, int nbPoints)
{
	
	float pi = glm::pi<float>();

	std::vector<glm::vec2> points;
	std::vector<GLuint> indices;
	int nbIndices;
	//wireFrameBuffers = {0,0,0};

	switch (type)
	{
	case PrimitiveType::Circle:
		nbIndices = 62;
	
		points.push_back(glm::vec2(0, 0));


		//Reversed the ordre but it doesn't really matter
		for (int i = nbIndices - 2; i >= 0; i--)
		{

			real t = i * (2 * pi) / (nbIndices - 2);



			points.push_back(glm::vec2(glm::cos(t),glm::sin(t)));
			indices.push_back(nbIndices - i - 2);


		}


		indices.push_back(1);


		break;

	case PrimitiveType::Rectangle:
		nbIndices = 5;
		points.push_back(glm::vec2(-0.5f, -0.5f));


		points.push_back(glm::vec2(-0.5f, 0.5f));


		points.push_back(glm::vec2(0.5f, 0.5f));


		points.push_back(glm::vec2(0.5f, -0.5f));




		indices.push_back(0);

		for (int i = 0; i < 4; i++)
		{
			indices.push_back(3 - i);

		}

		break;

	case PrimitiveType::Polygon:

		break;
	}

	//Setup des wireframe buffers
	glGenVertexArrays(1, &wireFrameBuffers.VAO);
	glGenBuffers(1, &wireFrameBuffers.VBO);
	glGenBuffers(1, &wireFrameBuffers.EBO);

	glBindVertexArray(wireFrameBuffers.VAO);
	glBindBuffer(GL_ARRAY_BUFFER, wireFrameBuffers.VBO);
	//glBufferData(GL_ARRAY_BUFFER, shape->points.size() * sizeof(real), shape->points.data(), GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, points.size() * 2 * sizeof(real), points.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, wireFrameBuffers.EBO);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(real), (void*)0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(real), (void*)0);

	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	wireFrameBuffers.nbIndices = nbIndices;


	std::vector<GLuint> triangulationIndices = triangulate(points);
	//Setup des solid buffers
	glGenVertexArrays(1, &solidBuffers.VAO);
	glGenBuffers(1, &solidBuffers.VBO);
	glGenBuffers(1, &solidBuffers.EBO);

	glBindVertexArray(solidBuffers.VAO);
	glBindBuffer(GL_ARRAY_BUFFER, solidBuffers.VBO);
	//glBufferData(GL_ARRAY_BUFFER, shape->points.size() * sizeof(real), shape->points.data(), GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, points.size() * 2 * sizeof(real), points.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, solidBuffers.EBO);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangulationIndices.size() * sizeof(GLuint), triangulationIndices.data(), GL_STATIC_DRAW);

	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(real), (void*)0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(real), (void*)0);

	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	solidBuffers.nbIndices = triangulationIndices.size();



		
}


void Primitive::drawWireFrame()
{
	//wireFrameBuffers.VAO
	glBindVertexArray(wireFrameBuffers.VAO);
	glDrawElements(GL_LINE_STRIP, wireFrameBuffers.nbIndices, GL_UNSIGNED_INT, 0);
}
void Primitive::drawSolid()
{
	glBindVertexArray(solidBuffers.VAO);
	glDrawElements(GL_TRIANGLES, solidBuffers.nbIndices, GL_UNSIGNED_INT, 0);
}


std::vector<GLuint> triangulate(const std::vector<glm::vec2>& points)
{
	assert(points.size() > 2);
	std::vector<GLuint> triangulationIndices;
	
	for (int i = 2; i < points.size(); i++)
	{
		triangulationIndices.push_back(0);
		triangulationIndices.push_back(i - 1);
		triangulationIndices.push_back(i);
	}

	return triangulationIndices;

}