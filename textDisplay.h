#include "entity.h"

class textDisplay : public entity
{
public:
	float movementSpeed = 2;
	string myString = "blood";
	int counter = 0;
	int lifeTime = 2;
	bool destroy = false;

	textDisplay();
	void update();
	//void updateMovement();
};

