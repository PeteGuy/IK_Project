#include "PhysicProcess.h"





namespace PhysicProcess
{
	std::vector<std::unique_ptr<RigidBody>> bodies;
	
	std::vector<Manifold> manifolds;
	glm::vec2 gravity = glm::vec2(0, 9.81f);
	
	glm::vec2 zero2(0.0f,0.0f);
	glm::vec2 test[] = {zero2,zero2};
	
	void BroadPhase()
	{
		
		manifolds.clear();

	

		for (auto bodyA = bodies.begin(); bodyA != bodies.end(); bodyA++)
		{
			for (auto bodyB = bodies.begin(); bodyB != bodies.end(); bodyB++)
			{
				if (bodyA == bodyB )
				{
					continue;
				}
				//if A and B are on the same layer then don't collide them (not fully implemented for now)
				if ((*bodyA)->layer & (*bodyB)->layer)
				{
					//continue;
				}

				if (quickAABBvsAABB((*bodyA)->getDefaultAABB(), (*bodyB)->getDefaultAABB()))
				{
					
					manifolds.push_back(
						{
							(*bodyA).get(),
							(*bodyB).get(),
							
							

						});
				}
			}
		}

		

		//Remove duplicates manifolds
		
		
		for (int i =0; i <manifolds.size(); i++)
		{
			int j = i + 1;
			while (j < manifolds.size())
			{
				if (manifolds[i].A == manifolds[j].B)
				{
					if (manifolds[i].B == manifolds[j].A)
					{

						manifolds.erase(manifolds.begin()+j);


						continue;
					}
				}

				j++;
			}
		}




	}
	

	void NarrowPhase()
	{

		//std::cout << manifolds.size() << " manifolds are about to be processed\n";
		for (auto m = manifolds.begin(); m < manifolds.end(); m++)
		{
			if (collisionFunctions[(int)m->A->shape->type][(int)m->B->shape->type](&(*m)))
			{
				actOnCollision(&(*m));

			}
			
		}
	}

	void applyGravity()
	{
		for (auto body = bodies.begin(); body != bodies.end(); body++)
		{
			
			(*body)->applyForce(gravity* (*body)->mass);
			
		}
	}

}
	
	

	