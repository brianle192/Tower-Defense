//
//  player.h


#ifndef __InstallingSFML__player__
#define __InstallingSFML__player__

#include "entity.h"

class player : public entity
{
public:
	int movementSpeed = 2;
	int attackDamage = 5;
	int counterWalking = 0;
	int direction = 0; // 1 - up, 2 - down, 3 - left, 4 - right

	player();
	void update();
	void updateMovement();
};

#endif /* defined(__InstallingSFML__player__) */
