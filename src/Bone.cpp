#include "Bone.h"


void setAngle(float mouseX, float mouseY, Bone* bone)
{
	glm::vec2(1, 0);

	glm::vec2 vectorToMouse = { mouseX - 400,mouseY - 300 };
	
	
	bone->angle = atan2(vectorToMouse.y, vectorToMouse.x);
}