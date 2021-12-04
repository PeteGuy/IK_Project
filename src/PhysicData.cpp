#include "PhysicData.h"



namespace PhysicData
{
	MassData defaultMassData
	{
		20.0f,
		calculateSafeInverse(20.0f),
		0.0f,
		calculateSafeInverse(20.0f)
	};



	MaterialData defaultMatDat
	{
		20.0f,
		0.9f,
		0.1f,
		0.05f
	};

	real calculateSafeInverse(real mass)
	{
		return (mass != 0) ? 1 / mass : 0;
	}
}
