#pragma once
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

#include <vector>
#include "Shapes.h"
#include "PhysicData.h"
#include "Macros.h"


#define COM_FLAG true
class RigidBody
{
public:
	RigidBody();
	RigidBody(Shape* shape, real x, real y);
	RigidBody(Shape*,real x,real y, PhysicData::MassData massdat, PhysicData::MaterialData matdat);
	RigidBody(Shape*, real x, real y, real mass, real inertia,real density,real restitution,real staticFriction,real dynamicFriction,uint32_t layer);

	//virtual void initialize();

	void applyForce(glm::vec2 force);
	void applyImpulse(const glm::vec2& impulse,const glm::vec2& contactPoint);
	
	void render();
	void update();
	AABB getDefaultAABB();
	//This is a test function
	
		
	
	Shape* shape;

	unsigned int vbo;
	unsigned int vao;
	unsigned int ebo;
	//std::vector<real> points;
	// Careful, uint only goes up to 255
	//std::vector<GLuint> indices;

	//Mass data
	real mass;
	real inv_mass;
	// For rotations not currently implemented
	real inertia;
	real inv_inert;

	//Material data
	real density;
	real restitution;
	real staticFriction;
	real dynamicFriction;

	//Transform data
	glm::vec2 position = glm::vec2(0.0f, 0.0f);
	glm::vec2 velocity = glm::vec2(0.0f, 0.0f);
	//angle (in radian)
	real angle = 0;
	// in radian per time unit
	real angularVelocity = 0;

	// Forces 
	glm::vec2 force;

	glm::vec2 min;
	glm::vec2 max;

	// Rotation matrice for polygons collision
	glm::mat2 rotationMat;

	uint32_t layer;
	//glm::mat2:

	//glm::vec2 com;
	unsigned int COMvbo;
	unsigned int COMvao;

	/*
	PhysicData::TransformData transform;
	PhysicData::MassData massInfo;
	PhysicData::MaterialData matInfo;
	
	//real gravityScale;
	// Primary data used to calculate AABB during broad phase
	

	PhysicData::TransformData previousTransform;
	PhysicData::TransformData CurrentTransform;*/
	
};