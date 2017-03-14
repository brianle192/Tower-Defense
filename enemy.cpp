#include "enemy.h"

enemy::enemy()
{
	rect.setSize(sf::Vector2f(50.0f, 50.0f));
	rect.setPosition(360.0f, 240.0f);
	rect.setFillColor(sf::Color::Blue);
	//sprite.setTextureRect(sf::IntRect(49 * 4, 0, 49, 49));
	
}

void enemy::update()
{
	sprite.setPosition(rect.getPosition());
}

void enemy::updateMovement()
{
	
	if (direction == 1) // Up
	{
		rect.move(0, -movementSpeed);
	}
	else if (direction == 2) // Down
	{
		rect.move(0, movementSpeed);
	}
	else if (direction == 3) // Left
	{
		rect.move(-movementSpeed, 0);
		
	}
	else if (direction == 4) // Right
	{
		rect.move(movementSpeed, 0);
		
	}
	else
	{
		// No movement
	}

	counterWalking++;
	if (counterWalking == 1)
	{
		counterWalking = 0;
	}

	counter++;
	if (counter >= movementLength)
		//if (counter >= 40)
	{
		direction = generateRandom(20);
		//direction = generateRandom(10);
		
		counter = 0;
	}

}
