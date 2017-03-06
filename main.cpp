
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
using namespace std;
#include <iostream>

#include "player.h"
#include "entity.h"
#include "projectile.h"
#include "enemy.h"


int main(int, char const**)
{

	// Variables
	float playerMovementSpeed = 2;
	int counterWalking = 0;
	int counter = 0;
	int counter2 = 0;
	int counter3 = 0;


	// Create the main window
	sf::RenderWindow window(sf::VideoMode(720, 480), "Fight Hard Yeah! Tower Defense Game");
		
	//Attempting to put the background Image in
	sf::RectangleShape background(sf::Vector2f(720.0f, 480.0f));
	background.setPosition(0.0f, 0.0f);

	sf::Texture backgroundImage;
	//backgroundImage.loadFromFile("Woods.png");
	backgroundImage.loadFromFile("mario.png");
	background.setTexture(&backgroundImage);


	sf::RectangleShape backgroundTree(sf::Vector2f(150.0f, 150.0f));
	backgroundTree.setPosition(330.0f, 180.0f);

	sf::Texture treeTexture;
	treeTexture.loadFromFile("transparent_tree.png");
	backgroundTree.setTexture(&treeTexture);


	sf::Texture textureEnemy;
	if (!textureEnemy.loadFromFile("enemySpriteSheet.png")) {
		return EXIT_FAILURE;
	}

	// Load a sprite to display
	sf::Texture texturePlayer;
	if (!texturePlayer.loadFromFile("spriteWalk.png")) {
		return EXIT_FAILURE;
	}
	sf::Sprite spritePlayer(texturePlayer);
	spritePlayer.setPosition(window.getSize().x / 2, window.getSize().y / 2);
	spritePlayer.setTextureRect(sf::IntRect(0, 0, 32, 32));





		// Load a music to play
	sf::Music music;
	if (!music.openFromFile("Punks.wav")) {
		return EXIT_FAILURE;
	}
		// Play the music
	music.play();
	

	// Class Object
	class player Player1;
	Player1.sprite.setTexture(texturePlayer);

	// Projectile Vector Array
	vector<projectile>::const_iterator iter;
	vector<projectile> projectileArray;

	// Projectile Object
	class projectile projectile1;


	// Enemy Vector Array
	vector<enemy>::const_iterator iter4;
	vector<enemy> enemyArray;

	// Enemy Object
	class enemy enemy1;
	enemy1.sprite.setTexture(textureEnemy);
	//enemy1.sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));

	enemy1.rect.setPosition(600, 200);
	enemyArray.push_back(enemy1);






	
	// Start the game loop
	while (window.isOpen())
	{
		// Process events
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close window: exit
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			// Escape pressed: exit
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
				window.close();
			}
		}

		// Clear screen
		window.clear();

		// Draw the sprite
		//window.draw(sprite);
		window.draw(backgroundTree);
		window.draw(background);
		// Draw the string
		//window.draw(text);

		// Fires Missle (Space bar)
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
		{
			enemy1.rect.setPosition(generateRandom(window.getSize().x), generateRandom(window.getSize().y));
			enemyArray.push_back(enemy1);
		}





		// Fires Missle (Space bar)
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			projectile1.rect.setPosition(Player1.rect.getPosition().x + Player1.rect.getSize().x / 2 - projectile1.rect.getSize().x / 2, Player1.rect.getPosition().y + Player1.rect.getSize().y / 2 - projectile1.rect.getSize().y / 2);
			projectile1.direction = Player1.direction;
			projectileArray.push_back(projectile1);
		}

		// Draw Projectiles
		counter = 0;
		for (iter = projectileArray.begin(); iter != projectileArray.end(); iter++)
		{
			projectileArray[counter].update(); // Update Projectile
			window.draw(projectileArray[counter].rect);

			counter++;
		}

		// Draw Enemies
		counter = 0;
		for (iter4 = enemyArray.begin(); iter4 != enemyArray.end(); iter4++)
		{
			enemyArray[counter].update();
			enemyArray[counter].updateMovement();
			//window.draw(enemyArray[counter].rect);
			window.draw(enemyArray[counter].sprite);

			counter++;
		}

		// Update Player
		Player1.update();
		Player1.updateMovement();

		// Draw Player
		window.draw(Player1.sprite);
		//window.draw(Player1.rect);

		// Update the window
		window.display();
	}

	return EXIT_SUCCESS;
}



