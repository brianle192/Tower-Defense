#include "textDisplay.h"

textDisplay::textDisplay()
{
	text.setFillColor(sf::Color::Red);
	text.setCharacterSize(15);
	text.setString(myString);
}

void textDisplay::update()
{
	text.move(0, -movementSpeed);

	counter++;
	if (counter >= lifeTime)
	{
		destroy = true;
	}
}
