#pragma once
#include "Macros.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace PhysicData
{
	struct MassData
	{
		real mass;
		real inv_mass;

		// For rotations (not covered in this article)
		real inertia;
		real inv_inert;
	};

	struct MaterialData
	{
		real density;
		real restitution;

		real staticFriction;
		real dynamicFriction;
	};

	struct TransformData
	{
		glm::vec2 position = glm::vec2(0.0f,0.0f);
		glm::vec2 velocity = glm::vec2(0.0f, 0.0f);;

		real angle = 0;
		real angularVelocity = 0;
	};

	real calculateSafeInverse(real mass);

	extern MassData defaultMassData;
	extern MaterialData defaultMatDat;
}
