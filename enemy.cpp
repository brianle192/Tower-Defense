//
//  enemy.cpp


#include "enemy.h"

enemy::enemy()
{
	rect.setSize(sf::Vector2f(32, 32));
	rect.setPosition(400, 200);
	rect.setFillColor(sf::Color::Blue);
	sprite.setTextureRect(sf::IntRect(49 * 4, 0, 49, 49));
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
		sprite.setTextureRect(sf::IntRect((49 * 4) + 49 * counterWalking, 0, 49, 49));
	}
	else if (direction == 4) // Right
	{
		rect.move(movementSpeed, 0);
		sprite.setTextureRect(sf::IntRect((49 * 6) + 49 * counterWalking, 0, 49, 49));
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
	{
		direction = generateRandom(10);
		counter = 0;
	}

}
