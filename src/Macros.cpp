#include "Macros.h"

float crossVec2(const glm::vec2& a, const glm::vec2& b)
{
	return (a.x * b.y - a.y * b.x);
}