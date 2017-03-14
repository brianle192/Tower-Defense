#include "entity.h"
#include "random.h"

class enemy : public entity
{
public:
	//float movementSpeed = 0.5;
	int movementSpeed = 1;
	int movementLength = 100;
	int attackDamage = 2;
	int counterWalking = 0;
	int direction = 0; // 1 - up, 2 - down, 3 - left, 4 - right
	int counter = 0;

	enemy();
	void update();
	void updateMovement();
};


