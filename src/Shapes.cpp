#include "Shapes.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

Shape::Shape()
{
	
}

/*CircleShape* Shape::getCircleShape()
{
	return NULL;
}
AABB_Shape* Shape::getAABB_Shape()
{
	return NULL;
}
PolygonShape* Shape::getPolygonShape()
{
	return NULL;
}*/


CircleShape::CircleShape(real radius) : Shape()
{
	// Default number of points to draw the circle (60 on the circumference and 1 for the radius line and another one to draw the final line) 
	nbPoints = 62; 
	this->radius = radius;
	type = ShapeType::Circle;
}

void CircleShape::setPoints()
{
	

	

	this->vecPoints.push_back(glm::vec2(0, 0));


	//Reversed the ordre but it doesn't really matter
	for (int i = nbPoints - 2; i >= 0; i--)
	{

		real t = i * (2 * glm::pi<real>()) / (nbPoints - 2);
		

		
		this->vecPoints.push_back(glm::vec2(radius * glm::cos(t), radius * glm::sin(t)));
		this->indices.push_back(nbPoints - i - 2);


	}
	

	this->indices.push_back(1);






}

glm::vec2 CircleShape::getDimensions()
{
	return glm::vec2(2 * radius, 2 * radius);
}


AABB_Shape::AABB_Shape(real width, real height)
{
	nbPoints = 5;
	this->width = width;
	this->height = height;
	type = ShapeType::AABB;
}



void AABB_Shape::setPoints()
{
	
	this->vecPoints.push_back(glm::vec2(-width / 2, -height / 2));
	

	this->vecPoints.push_back(glm::vec2(-width / 2, height / 2));
	

	this->vecPoints.push_back(glm::vec2(width / 2, height / 2));
	

	this->vecPoints.push_back(glm::vec2(width / 2, -height / 2));
	



	this->indices.push_back(0);
	
	for (int i = 0; i < 4; i++)
	{
		this->indices.push_back(3-i);
	
	}
	
}

glm::vec2 AABB_Shape::getDimensions()
{
	return glm::vec2(width, height);
}

PolygonShape::PolygonShape(float vertices[],int nbPoints)
{
	// the vertices array has to be a serie of 2 dimensional vectors (no z axis)
	assert(nbPoints >= 3);// We want at least three points to form a polygone
	this->nbPoints = nbPoints+1; // we have to add one to render it fully 
	//int testarr[] = { 1,2,3,4,5 };
	this->indices.push_back(0);

	for (int i = 0; i < nbPoints; i++)
	{
		this->indices.push_back(nbPoints-1 - i);

	}
	//this->points = std::vector<real>(vertices,vertices+(nbPoints*2));
	for (int i = 0; i < nbPoints; i++)
	{
		this->vecPoints.push_back(glm::vec2(vertices[i*2], vertices[(i*2) + 1]));
	}
	


	
	type = ShapeType::Polygon;
	
	calculateCOM();
	setPoints();
	
	setNormals();
	//points
}

void PolygonShape::setPoints()
{
	
	//This method simply translate every point in order to have the origin be the center of mass
	for (auto it = vecPoints.begin(); it < vecPoints.end(); it ++)
	{
		*it = *it - com;
		
		//*it = *it - com.x;
		//*(it + 1) = *(it + 1) - com.y;
	}

	
	com = glm::vec2();
	

}

glm::vec2 PolygonShape::getDimensions()
{
	return glm::vec2();
}

void PolygonShape::setNormals()
{
	/*for (auto it = points.begin(); it != points.end()-3; it+=3)
	{												// x values    
		normals.push_back(glm::normalize(glm::vec2(*(it + 3 + 1) - *(it + 1), -(*(it + 3) - *it))));
	}*/
}


void PolygonShape::calculateCOM()
{
	com = glm::vec2();
	//we want everypoint but one of them is repeated
	for (auto it = vecPoints.begin(); it < vecPoints.end(); it++)
	{
		
		com += *it;
		

	}

	com /= nbPoints - 1;
	//std::cout << "COM is at x = " << com.x << "," << com.y << "\n";
}

