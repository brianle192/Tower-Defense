
// Adding Enemy Class


#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include "Animation.h"
#include "Player.h"
#include "Audio.h"
#include "entity.h"
#include "projectile.h"
#include "enemy.h"




using namespace std;
int exitgame = 0;
void inittextures();

//Work on separating textures
//Problems with keyboard input being read as many times per second button was pressed



int main() {

	// Variables
	float playerMovementSpeed = 2;
	int counterWalking = 0;
	int counter = 0;
	int counter2 = 0;
	int counter3 = 0;

	sf::RenderWindow window(sf::VideoMode(720, 480), "Fight Hard Yeah! Tower Defense Game", sf::Style::Close | sf::Style::Resize);
	Audio audio;

	//Player character texture, rectangle bound to box
	sf::Texture playerTexture;
	//Assigning the sprite sheet to the player
	playerTexture.loadFromFile("char_sprite_walk3.png");
	Player player(&playerTexture, sf::Vector2u(3, 3), 0.3f, 100.0f);



	//Attempting to put the background Image in
	sf::RectangleShape background(sf::Vector2f(720.0f, 480.0f));
	background.setPosition(0.0f, 0.0f);

	//Map
	sf::Texture backgroundImage;
	backgroundImage.loadFromFile("mario.png");
	background.setTexture(&backgroundImage);

	//Transparent Tree
	sf::RectangleShape backgroundTree(sf::Vector2f(150.0f, 150.0f));
	backgroundTree.setPosition(330.0f, 180.0f);
	sf::Texture treeTexture;
	treeTexture.loadFromFile("transparent_tree.png");
	backgroundTree.setTexture(&treeTexture);

	//Enemy
	sf::Texture textureEnemy;
	if (!textureEnemy.loadFromFile("enemySpriteSheet.png")) {
		return EXIT_FAILURE;
	}

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
	
	//Menu
	sf::RectangleShape menuImage(sf::Vector2f(720.0f, 480.0f));
	menuImage.setPosition(0.0f, 0.0f);
	sf::Texture menuTexture;
	menuTexture.loadFromFile("menu_1.png");
	menuImage.setTexture(&menuTexture);

	//Clock for sprite rotation
	float deltaTime = 0.0f;
	sf::Clock clock;

	//Assigning Player Footstep Sounds
	if (!player.soundBuf.loadFromFile("foot.wav"))
		std::cout << "can't open sound file" << std::endl;
	player.sound.setBuffer(player.soundBuf);
	player.sound.setVolume(100);


	//maybe put in a structure that takes the options menu
	//then put a flag 
	//if(music = 1) play
	//if(music = 2) play

	//Playing Background Music
	cout << "Playing background music" << endl;
	audio.backgroundmusic1.play();
	audio.backgroundmusic1.setVolume(25);


	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			}

		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
		{
			exitgame += 1;
			for (int i = 0; i < 1; i++) {
				//while(window.isOpen()) {
				cout << exitgame << endl;
				std::cout << "Menu Being Displayed" << std::endl;
				window.setVisible(true);
				window.draw(menuImage);
				window.display();
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
				{
					//Are you sure you want to exit?
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
						return 0;
					}

					//window.clear();
					//break;
				}
				//}
			}
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


		player.Update(deltaTime);
		window.clear(sf::Color(125, 125, 125));
		window.draw(background);
		player.Draw(window);
		window.draw(backgroundTree);
		window.display();
	}
	return 0;
}


void inittextures() {



}


/*Old Comments*/

//1 old animation sf::RectangleShape player(sf::Vector2f(100.0f, 150.0f));
//player.setFillColor(sf::Color::Magenta);
//player.setOrigin(50.0f, 50.0f);
//1 old animation player.setPosition(206.0f, 206.0f);


//background.setOrigin(250.0f, 250.0f);
//background.setPosition(250.0f, 250.0f);



/*case sf::Event::Resized:
//std::cout << "New window width " << evnt.size.width << "New window height " << evnt.size.height << std::endl;
printf("New window width: %i New window height: %i \n", evnt.size.width, evnt.size.height);
break;
case sf::Event::TextEntered:
if (evnt.text.unicode < 128)
{
printf("%c", evnt.text.unicode);
}
*/


/*
if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
{
player.move(0.1f, 0.0f);
}
if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
{
player.move(0.0f, -0.1f);
}
if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
{
player.move(0.f, 0.1f);
}
*/
/*
if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
{
sf::Vector2i mousePos = sf::Mouse::getPosition(window);
player.setPosition(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
}
*/
//old animation animation.Update(0, deltaTime, false);
//player.setTextureRect(animation.uvRect);

//window.clear();
//window.draw(player);


