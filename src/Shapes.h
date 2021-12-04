#pragma once
#include<glad/glad.h>
#include <vector>
#include "Macros.h"
enum class ShapeType  { Circle,AABB,Polygon,last };

class Shape
{
public:
	int nbPoints;
	//std::vector<real> points;
	std::vector<glm::vec2> vecPoints;
	// Careful, uint only goes up to 255
	std::vector<GLuint> indices;

	ShapeType type;

	Shape();
	virtual void setPoints() = 0;
	virtual glm::vec2 getDimensions() = 0;
	float radius;
	float width;
	float height;

	
};

class CircleShape : public Shape
{
public:
	CircleShape(real radius);
	//real radius;
	void setPoints() override;
	glm::vec2 getDimensions() override;
};

class AABB_Shape : public Shape
{
public:
	AABB_Shape(real width, real height);
	
	void setPoints() override;
	glm::vec2 getDimensions() override;

};


class PolygonShape : public Shape
{
public:
	PolygonShape(real vertices[], int nbPoints);
	void setPoints() override;
	glm::vec2 getDimensions() override;
	void setNormals();
	void calculateCOM();

	std::vector<glm::vec2> normals;
	glm::vec2 com;
	
};

struct AABB
{
	glm::vec2 min;
	glm::vec2 max;
};