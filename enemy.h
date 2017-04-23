//#include "entity.h"
#pragma once
#include <SFML/Graphics.hpp>
#include "random.h"

class enemy
{
public:
	//float movementSpeed = 0.5; // slower
	int movementSpeed = 2;
	int movementLength = 100; // 50
	int attackDamage = 1;
	/////
	double enemyAttackDamage1 = 0.3;
	double enemyAttackDamage2 = 0.2;
	double enemyAttackDamage3 = 0.1;
	/////
	int counterWalking = 0;
	int direction = 0; // 1 - up, 2 - down, 3 - left, 4 - right
	int counter = 0;
	
    int hp1 = 3;
	int hp2 = 2;
	int hp3 = 1;
	int maxhp1 = 3;
	int maxhp2 = 2;
	int maxhp3 = 1;

    bool alive = true;

	// Add for collision with wall
	bool faceRight = true;
	bool faceLeft = true;
	bool faceUp = true;
	bool faceDown = true;
	// Add for chasing AI
	bool chase = true;
	bool aggroed = false;
	//bool spawn = false;

	int spritex = 32;
	int spritey = 32;
	int spritexStart = 0;
	int spriteyStart = 0;


	//Added from Entity.h
	sf::RectangleShape rect;
	sf::Sprite sprite;
	sf::Text text;

	enemy();
	void update();
	void updateMovement();
};


