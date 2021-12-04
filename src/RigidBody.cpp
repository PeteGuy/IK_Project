#include "RigidBody.h"
#include "timeOperations.h"
//#include <glm/detail/func_geometric.inl>


RigidBody::RigidBody()
{
	// We use default values for now

	shape = new AABB_Shape(40.0f, 40.0f);

	//Mass info
	mass = 20.0f;
	inv_mass = PhysicData::calculateSafeInverse(mass);
	inertia = 0.0f;
	inv_inert = PhysicData::calculateSafeInverse(inertia);

	//Material info
	density = 20.0f;
	restitution = 0.9f;
	staticFriction = 0.1f;
	dynamicFriction = 0.05f;

	//Transform info
	position = glm::vec2(0, 0);
	velocity = glm::vec2(0.0f, 0.0f);;
	angle = 0.0f;
	angularVelocity = 0.0f;

	force = glm::vec2(0.0f, 0.0f);
	layer = 2;

	glm::vec2 dimensions = shape->getDimensions();
	min = glm::vec2(-dimensions.x / 2, -dimensions.y / 2);
	max = glm::vec2(dimensions.x / 2, dimensions.y / 2);

	this->shape = shape;
	shape->setPoints();

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//glBufferData(GL_ARRAY_BUFFER, shape->points.size() * sizeof(real), shape->points.data(), GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, shape->vecPoints.size() * 2 * sizeof(real), shape->vecPoints.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, shape->indices.size() * sizeof(GLuint), shape->indices.data(), GL_STATIC_DRAW);

	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(real), (void*)0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(real), (void*)0);

	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	
	
}

RigidBody::RigidBody(Shape* shape,real x,real y)
{
	
	
	// We use default values for now
	
	//Mass info
	mass = 20.0f;
	inv_mass = PhysicData::calculateSafeInverse(mass);
	inertia = 0.0f;
	inv_inert = PhysicData::calculateSafeInverse(inertia);

	//Material info
	density = 20.0f;
	restitution = 0.9f;
	staticFriction = 0.1f;
	dynamicFriction = 0.05f;

	//Transform info
	position = glm::vec2(x, y);
	velocity = glm::vec2(0.0f, 0.0f);;
	angle = 0.0f;
	angularVelocity = 0.0f;

	force = glm::vec2(0.0f, 0.0f);
	layer = 2;

	glm::vec2 dimensions = shape->getDimensions();
	min = glm::vec2(-dimensions.x/2,-dimensions.y/2);
	max = glm::vec2(dimensions.x/2,dimensions.y/2);

	this->shape = shape;
	shape->setPoints();


	if (COM_FLAG && shape->type == ShapeType::Polygon)
	{
		
	
		//std::cout << "com is at " << com.x << ", " << com.y << "\n";
		real comDATA[] = { 0.0f,0.0f,0.0f };
		glGenVertexArrays(1, &COMvao);
		glGenBuffers(1, &COMvbo);
		glBindVertexArray(COMvao);
		glBindBuffer(GL_ARRAY_BUFFER, COMvbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(comDATA),comDATA , GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(real), (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//glBufferData(GL_ARRAY_BUFFER, shape->points.size() * sizeof(real), shape->points.data(), GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, shape->vecPoints.size() * 2 * sizeof(real), shape->vecPoints.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, shape->indices.size() * sizeof(GLuint), shape->indices.data(), GL_STATIC_DRAW);

	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(real), (void*)0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(real), (void*)0);

	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

/////Attention !!!!!!!!!!!!!!! ces constructeurs utilisent toujours un système de vecteurs 3, il doit être corrigé avant d'être utiliser
RigidBody::RigidBody(Shape*, real x, real y, PhysicData::MassData massdat, PhysicData::MaterialData matdat)
{
	//Mass info
	mass = massdat.mass;
	inv_mass = PhysicData::calculateSafeInverse(mass);
	inertia = massdat.inertia;
	inv_inert = PhysicData::calculateSafeInverse(inertia);

	//Material info
	density = matdat.density;
	restitution = matdat.restitution;
	staticFriction = matdat.staticFriction;
	dynamicFriction = matdat.dynamicFriction;

	//Transform info
	position = glm::vec2(x, y);
	velocity = glm::vec2(0.0f, 0.0f);;
	angle = 0.0f;
	angularVelocity = 0.0f;

	force = glm::vec2(0.0f, 0.0f);
	layer = 2;

	glm::vec2 dimensions = shape->getDimensions();
	min = glm::vec2(-dimensions.x / 2, -dimensions.y / 2);
	max = glm::vec2(dimensions.x / 2, dimensions.y / 2);



	this->shape = shape;
	shape->setPoints();

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//glBufferData(GL_ARRAY_BUFFER, shape->points.size() * sizeof(real), shape->points.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, shape->indices.size() * sizeof(GLuint), shape->indices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(real), (void*)0);

	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

RigidBody::RigidBody(Shape*, real x, real y, real mass, real inertia, real density, real restitution, real staticFriction, real dynamicFriction, uint32_t layer)
{
	//Mass info
	this->mass = mass;
	this->inv_mass = PhysicData::calculateSafeInverse(mass);
	this->inertia = inertia;
	this->inv_inert = PhysicData::calculateSafeInverse(inertia);

	//Material info
	this->density = density;
	this->restitution = restitution;
	this->staticFriction = staticFriction;
	this->dynamicFriction = dynamicFriction;

	//Transform info
	position = glm::vec2(x, y);
	velocity = glm::vec2(0.0f, 0.0f);;
	angle = 0.0f;
	angularVelocity = 0.0f;

	force = glm::vec2(0.0f, 0.0f);
	layer = 2;

	glm::vec2 dimensions = shape->getDimensions();
	min = glm::vec2(-dimensions.x / 2, -dimensions.y / 2);
	max = glm::vec2(dimensions.x / 2, dimensions.y / 2);



	this->shape = shape;
	shape->setPoints();

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//glBufferData(GL_ARRAY_BUFFER, shape->points.size() * sizeof(real), shape->points.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, shape->indices.size() * sizeof(GLuint), shape->indices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(real), (void*)0);

	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


void RigidBody::render()
{
	// body render is currently fully handled by the render namespace (to reconsider)
	
	/*
	glBindVertexArray(vao);
	glDrawElements(GL_LINE_STRIP, shape->nbPoints, GL_UNSIGNED_INT, 0);

	
	if (COM_FLAG && shape->type == ShapeType::Polygon)
	{
		
		glBindVertexArray(COMvao);
		glDrawArrays(GL_POINTS, 0, 1);
		
		
	}
	
	*/
}


void RigidBody::update()
{

	
	velocity += (force * inv_mass)*dtValue;
	
	position += velocity * dtValue;
	angle += angularVelocity * dtValue;
	
	rotationMat = glm::mat2(cos(angle),sin(angle),-sin(angle),cos(angle));
	force = glm::vec2(0.0f,0.0f);
}

//Returns light AAB which allows for easy calculation during broad phase
AABB RigidBody::getDefaultAABB()
{
	return AABB{min-position,max-position};
}

void RigidBody::applyForce(glm::vec2 force)
{
	this->force += force;
}

void RigidBody::applyImpulse(const glm::vec2& impulse, const glm::vec2& contactPoint)
{
	velocity += inv_mass * impulse;
	angularVelocity += inv_inert * crossVec2(contactPoint,impulse);
	
	
}

