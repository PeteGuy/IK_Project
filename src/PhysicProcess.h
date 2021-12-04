#pragma once
#include "RigidBody.h"
#include "Collision.h"




namespace PhysicProcess
{
	void BroadPhase();
	void NarrowPhase();
	void applyGravity();

	extern std::vector<std::unique_ptr<RigidBody>> bodies;
	extern std::vector<Manifold> manifolds;
	extern glm::vec2 gravity;
	
}