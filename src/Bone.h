#pragma once
#include "Macros.h"



struct Bone
{
	float length;
	float angle;
	glm::vec2 position;
};

void setAngle(float mouseX, float mouseY, Bone* bone);