
#pragma once
#include <SFML/Graphics.hpp>
//#include "entity.h"

class projectile 
{
public:
	int movementSpeed = 20; //20
	int attackDamage = 1; // 1
	int direction = 0; // 1 - up, 2 - down, 3 - left, 4 - right
	bool destroy = false;
	int counterLifetime = 0;
	bool enemyProjectile = false;

	//Added from Entity.h
	sf::RectangleShape rect;
	sf::Sprite sprite;
	sf::Text text;

	projectile();
	void update();
	//void updateMovement();
};


