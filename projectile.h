//
//  projectile.h
//  InstallingSFML
//
//  Created by Blank Blank on 2015-08-11.
//  Copyright (c) 2015 Blank Blank. All rights reserved.
//

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