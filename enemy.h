//
//  enemy.h


#ifndef __InstallingSFML__enemy__
#define __InstallingSFML__enemy__

#include "entity.h"
#include "random.h"

class enemy : public entity
{
public:
	int movementSpeed = 1;
	int movementLength = 100;
	int attackDamage = 5;
	int counterWalking = 0;
	int direction = 0; // 1 - up, 2 - down, 3 - left, 4 - right
	int counter = 0;

	enemy();
	void update();
	void updateMovement();
};

#endif /* defined(__InstallingSFML__enemy__) */
