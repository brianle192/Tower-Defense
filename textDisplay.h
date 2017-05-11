#include "entity.h"

class textDisplay : public entity
{
public:
	float movementSpeed = 3;
	string myString = "blood";
	int counter = 0;
	int lifeTime = 5;
	bool destroy = false;

	textDisplay();
	void update();
	//void updateMovement();
};

