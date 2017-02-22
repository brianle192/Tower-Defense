//
//  projectile.h


#ifndef __InstallingSFML__projectile__
#define __InstallingSFML__projectile__

#include "entity.h"

class projectile : public entity
{
public:
	int movementSpeed = 10;
	int attackDamage = 5;
	int direction = 0; // 1 - up, 2 - down, 3 - left, 4 - right

	projectile();
	void update();
	//void updateMovement();
};


#endif /* defined(__InstallingSFML__projectile__) */
