#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Animation.h"
#include "Player.h"
#include "Audio.h"
#include "Graphic.h"
#include "enemy.h"
#include "Wall.h"
#include "projectile.h"
#include "random.h"
#include "entity.h"
#include "Resource.h"


using namespace std;
int exitgame = 0;
int pausedgame = 20;

int main()
{
	sf::RenderWindow window(sf::VideoMode(1024, 576), "Fight Hard Yeah! Tower Defense Game", sf::Style::Close | sf::Style::Resize);
	Audio audio;
	Graphic graphics;
	int flag = 0, counter = 0, help = 0, drawtower = 0;
	sf::Clock clock1; // clock for the projectile
	sf::Clock clock2;
	sf::Clock clock3;
	int counter2 = 0;
	int counter3 = 0;

//---------------------------------------------------------------------------------------------------------------
//Gerardo 
//Player character texture, rectangle bound to box
	sf::Texture playerTexture;
	playerTexture.loadFromFile("char_sprite_walk3.png");

	sf::RectangleShape playerRect;
	sf::Texture playerTexture2;
	playerTexture2.loadFromFile("player.png");
	playerRect.setSize(sf::Vector2f(40.0f, 40.0f));
	playerRect.setPosition(220.0f, 220.0f);
	playerRect.setTexture(&playerTexture2);
	sf::RectangleShape tower1;
	sf::RectangleShape tower2;
	sf::RectangleShape tower3;
	sf::Texture towertex1;
	sf::Texture towertex2;
	sf::Texture towertex3;
	towertex1.loadFromFile("tower1.png");
	tower1.setSize(sf::Vector2f(30.0f, 40.0f));
	towertex2.loadFromFile("tower2.png");
	tower2.setSize(sf::Vector2f(30.0f, 40.0f));
	towertex3.loadFromFile("tower3.png");
	tower3.setSize(sf::Vector2f(30.0f, 40.0f));
	tower1.setTexture(&towertex1);
	tower2.setTexture(&towertex2);
	tower3.setTexture(&towertex3);
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
//Miguel text on screen
	sf::Font font;
	if (!font.loadFromFile("arial.ttf")) {
		std::cout << "can't open ttf file" << std::endl;
	}
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(15);
	//text.setColor(sf::Color::Red);
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);
	text.setString("Level - 1\n");

	sf::Text textHelp;
	textHelp.setFont(font);
	textHelp.setCharacterSize(15);
	textHelp.setString("\n(H) Help?\n");
	sf::Text textHelp2;
	textHelp2.setFont(font);
	textHelp2.setCharacterSize(15);
	textHelp2.setString("\n(H) Help?\n(F) - Flashlight\n(Space) - Shoot\n(1) - Melee\n(2) - Sword\n(3) - Tower\n");
//---------------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------------------------
//Miguel Walls
	vector<Wall>::const_iterator wallit;
	vector<Wall> wallArray;

	
	class Wall wall1, wall2, wall3, wall4;

	wall1.rect.setPosition(0, 0);
	wall1.rect.setSize(sf::Vector2f(720, 160));
	wallArray.push_back(wall1);
	wall2.rect.setPosition(0, 340);
	wall2.rect.setSize(sf::Vector2f(150, 150));
	wallArray.push_back(wall2);
	wall3.rect.setPosition(150, 430);
	wall3.rect.setSize(sf::Vector2f(570, 50));
	wallArray.push_back(wall3);
	wall4.rect.setPosition(560, 240);
	wall4.rect.setSize(sf::Vector2f(30, 10));
	wallArray.push_back(wall4);

//---------------------------------------------------------------------------------------------------------------
//Miguel Resources	
	vector<Resource>::const_iterator resourceit;
	vector<Resource> resourceArray;
	class Resource resource1;
	//sf::Texture textureResource1;
	sf::Texture textureResource1, textureResource2, textureResource3;

	resource1.resource1 = true;
	resource1.resource2 = false;
	resource1.resource3 = false;
	textureResource1.loadFromFile("res1.png");
	resource1.rect.setTexture(&textureResource1);
	//resource1.rect.setFillColor(sf::Color::Green);
	resource1.rect.setPosition(300, 350);
	resourceArray.push_back(resource1);
	resource1.rect.setPosition(300, 400);
	resourceArray.push_back(resource1);
	resource1.resource1 = false;

	resource1.resource1 = false;
	resource1.resource2 = true;
	resource1.resource3 = false;
	textureResource2.loadFromFile("res2.png");
	resource1.rect.setTexture(&textureResource2);
	//resource1.rect.setFillColor(sf::Color::Blue);
	resource1.rect.setPosition(450, 250);
	resourceArray.push_back(resource1);
	resource1.rect.setPosition(400, 400);
	resourceArray.push_back(resource1);
	resource1.resource2 = false;

	resource1.resource1 = false;
	resource1.resource2 = false;
	resource1.resource3 = true;
	textureResource3.loadFromFile("res3.png");
	resource1.rect.setTexture(&textureResource3);
	//resource1.rect.setFillColor(sf::Color::Red);
	resource1.rect.setPosition(200, 250);
	resourceArray.push_back(resource1);
	resource1.rect.setPosition(200, 400);
	resourceArray.push_back(resource1);
	resource1.resource3 = false;
//---------------------------------------------------------------------------------------------------------------

	
//Gerardo Player Sprite/Sound
	Player player(&playerTexture, sf::Vector2u(3, 3), 0.3f, 100.0f);
//Assigning Player Footstep Sounds
	if (!player.soundBuf.loadFromFile("foot.wav"))
		//std::cout << "can't open sound file" << std::endl;
	player.sound.setBuffer(player.soundBuf);
	player.sound.setVolume(100);

//---------------------------------------------------------------------------------------------------------------
//Cuong
// Adding enemy texture - need to work more for sprite sheet
	sf::Texture textureEnemy;
	if (!textureEnemy.loadFromFile("ghost.png")) {
		return EXIT_FAILURE;
	}
	
// Adding enemy texture type 2 spawning randomly //////////////////// added on 04/01
	sf::Texture textureEnemy2;
	if (!textureEnemy2.loadFromFile("monster.png")) {
		return EXIT_FAILURE;
	}

// Enemy Vector Array
	vector<enemy>::const_iterator iter4;
	vector<enemy> enemyArray;
	vector<enemy> enemy1Array;   //////////////////////////////added on 04/01

// Enemy Objects - make 2 type enemies
	class enemy enemy1, enemy2; 

	enemy1.sprite.setTexture(textureEnemy); // y: 200 is the border with the wall
	//enemy1.sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	enemy1.rect.setPosition(700, 250);
	enemyArray.push_back(enemy1);
	

	enemy2.sprite.setTexture(textureEnemy2);
	enemy2.rect.setPosition(500, 260);
	enemy1Array.push_back(enemy2); ////////////////////add 04/01 enemy type 2 spawn randomly
	
//--------------------------------------------------------------------------------------------------

//Menu
	sf::RectangleShape menuImage(sf::Vector2f(720.0f, 480.0f));
	menuImage.setPosition(0.0f, 0.0f);
	sf::Texture menuTexture;
	menuTexture.loadFromFile("menu_1.png");
	menuImage.setTexture(&menuTexture);

//-----------------------------------------------------------------------------------------------------
//Gerardo Clock
	//Clock for sprite rotation
	float deltaTime = 0.0f;
	sf::Clock clock;

			
	//Playing Background Music
	//cout << "Playing background music" << endl;
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
		
			if (evnt.type == sf::Event::KeyPressed)
			{
				if (evnt.key.code == sf::Keyboard::Escape)
				{
					//std::cout << "Menu Being Displayed" << std::endl;
					if (exitgame == 0)
						exitgame = 1;
					else
						exitgame = 0;
				}
			}

			if (evnt.type == sf::Event::KeyPressed)
			{
				if (evnt.key.code == sf::Keyboard::P) {
					//pausedgame = 1;
					//Pauses the game for alloted seconds you only have so many seconds to pause
					if (pausedgame > 0) {
						sf::sleep(sf::seconds(10));
						std::cout << "Game Paused" << std::endl;
						pausedgame -= 10;
					}
				}
			}


///////////////////////////////////////////////////////////////////////////////////////// added after report 2
//---------------------------------------------------------------------------------------------------------------
//Gerardo
//Grabbing Left Button
			if (evnt.type == sf::Event::MouseButtonPressed)
			{
				/*if (evnt.key.code == sf::Mouse::Left)
				{
					std::cout << "left button clicked" << std::endl;
					sf::Vector2i position = sf::Mouse::getPosition(window);
					std::cout << position.x << std::endl;
					std::cout << position.y << std::endl;
				}*/

				if (evnt.key.code == sf::Mouse::Right)
				{
					drawtower = 1;
					sf::Vector2i positionTower = sf::Mouse::getPosition(window);
					std::cout << positionTower.x << std::endl;
					std::cout << positionTower.y << std::endl;

					//float posx = positionTower.x;
					//float posy = positionTower.y;

					if (player.tower == 3)
					{

						tower1.setPosition(positionTower.x, positionTower.y);
						player.tower--;
						std::cout << "Placing tower on x: " << positionTower.x << ",y: " << positionTower.y << std::endl;
						//window.draw(tower1);
					}
					if (player.tower == 2)
					{
						tower2.setPosition(positionTower.x, positionTower.y);
						player.tower--;
						std::cout << "Placing tower on x: " << positionTower.x << ",y: " << positionTower.y << std::endl;
						//window.draw(tower2);
					}
					if (player.tower == 1)
					{
						tower2.setPosition(positionTower.x, positionTower.y);
						player.tower--;
						std::cout << "Placing tower on x: " << positionTower.x << ",y: " << positionTower.y << std::endl;
						//window.draw(tower3);
					}
					//tower1.setPosition(positionTower.x, positionTower.y);
					//std::cout << "Placing tower on x: " << positionTower.x << ",y: " << positionTower.y << std::endl;

				}
			  }
			}


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::H))
		{
			help ^= 1;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1))
		{
			flag = 0;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2))
		{
			flag = 1;
		}
		if (flag == 0)
		{
			playerTexture.loadFromFile("char_sprite_walk3.png");
			
		}
		else if (flag == 1)
		{
			playerTexture.loadFromFile("char_sprite_walk_gun_1.png");
			
		}

//---------------------------------------------------------------------------------------------------------------
//Cuong
//Enemy Wall Collision
		counter = 0;
		for (iter4 = enemyArray.begin(); iter4 != enemyArray.end(); iter4++)
		{
			int counter2 = 0;
	
			for (wallit = wallArray.begin(); wallit != wallArray.end(); wallit++)
			{
				if (enemyArray[counter].rect.getGlobalBounds().intersects(wallArray[counter2].rect.getGlobalBounds()))
				{	//Hit wall
					if (enemyArray[counter].direction == 1) //Up
					{
						enemyArray[counter].faceUp = false;
						enemyArray[counter].rect.move(0, 1);
					}
					else if (enemyArray[counter].direction == 2) //Down
					{
						enemyArray[counter].faceDown = false;
						enemyArray[counter].rect.move(0, -1);
					}
					else if (enemyArray[counter].direction == 3) //Left
					{
						enemyArray[counter].faceLeft = false;
						enemyArray[counter].rect.move(1, 0);
					}
					else if (enemyArray[counter].direction == 4) //Right
					{
						enemyArray[counter].faceRight = false;
						enemyArray[counter].rect.move(-1, 0);
					}
					else 
					{
					}
				}
				counter2++;
			}

			counter++;
		}


//Enemy Wall Collision type 2 ////////////////////////////////////////////////////// added 04/01
		counter = 0;
		for (iter4 = enemy1Array.begin(); iter4 != enemy1Array.end(); iter4++)
		{
			int counter2 = 0;

			for (wallit = wallArray.begin(); wallit != wallArray.end(); wallit++)
			{
				if (enemy1Array[counter].rect.getGlobalBounds().intersects(wallArray[counter2].rect.getGlobalBounds()))
				{	//Hit wall
					if (enemy1Array[counter].direction == 1) //Up
					{
						enemy1Array[counter].faceUp = false;
						enemy1Array[counter].rect.move(0, 1);
					}
					else if (enemy1Array[counter].direction == 2) //Down
					{
						enemy1Array[counter].faceDown = false;
						enemy1Array[counter].rect.move(0, -1);
					}
					else if (enemy1Array[counter].direction == 3) //Left
					{
						enemy1Array[counter].faceLeft = false;
						enemy1Array[counter].rect.move(1, 0);
					}
					else if (enemy1Array[counter].direction == 4) //Right
					{
						enemy1Array[counter].faceRight = false;
						enemy1Array[counter].rect.move(-1, 0);
					}
					else
					{
					}
				}
				counter2++;
			}

			counter++;
		}
//---------------------------------------------------------------------------------------------------------------


		window.setView(player.view);

/////////////////////////////////////////////////////////////////////////////////////////////////////////// G + M Add 3/16
//Player Wall Collision
		counter = 0;
		for (wallit = wallArray.begin(); wallit != wallArray.end(); wallit++) {
			if (player.body.getGlobalBounds().intersects(wallArray[counter].rect.getGlobalBounds()))
			{
				//Hit wall
				if (player.direction == 1) //Up
				{
					player.faceUp = false;
					player.body.move(0, 1);
				}
				else if (player.direction == 2) //Down
				{
					player.faceDown = false;
					player.body.move(0, -1);
				}
				else if (player.direction == 3) //Left
				{
					player.faceLeft = false;
					player.body.move(1, 0);
				}
				else if (player.direction == 4) //Right
				{
					player.faceRight = false;
					player.body.move(-1, 0);
				}
				else {}
			}
			counter++;
		}
		
//Collision with Resources
		counter = 0;
		for (resourceit = resourceArray.begin(); resourceit != resourceArray.end(); resourceit++) {
			if (player.body.getGlobalBounds().intersects(resourceArray[counter].rect.getGlobalBounds()))
			{
				//Hit Resource
				if (resourceArray[counter].resource1 == true) //resource 1
				{
					player.health += 1;
					cout << "health: " << player.health << endl;
					resourceArray[counter].gathered = true;
				}
				if (resourceArray[counter].resource2 == true) //resource 2
				{
					player.ammo += 1;
					cout << "ammo: " << player.ammo << endl;
					resourceArray[counter].gathered = true;
				}
				if (resourceArray[counter].resource3 == true) //resource 3
				{
					player.tower += 1;
					cout << "tower: " << player.tower << endl;
					resourceArray[counter].gathered = true;
				}
			}
			counter++;
		}
		//Remove Resource
		counter = 0;
		for (resourceit = resourceArray.begin(); resourceit != resourceArray.end(); resourceit++)
		{
			if (resourceArray[counter].gathered == true)
			{
				resourceArray.erase(resourceit);  //clear() removes all
				break;
			}
			counter++;
		}
		//end---------------------------------------------------------------------------------------------------------------


		//window.setView(player.view);
		player.Update(deltaTime);
		// Draw the sprite
		window.clear(sf::Color(125, 125, 125));
        window.draw(graphics.background);
		window.draw(graphics.background2);
		window.draw(graphics.background3);
		window.draw(graphics.background4);
		window.draw(graphics.background5);
		
		//Draw Wall
		counter = 0;
		for (wallit = wallArray.begin(); wallit != wallArray.end(); wallit++)
		{
			wallArray[counter].update();

			window.draw(wallArray[counter].rect);
			window.draw(wallArray[counter].sprite);
			counter++;
		}


//////////////////////////////////////////////////////////////add after report 2

//window.setPosition(sf::Vector2i(50, 50));
		window.draw(graphics.backgroundTree);
		player.Draw(window);
		window.draw(wall1.sprite);
		window.draw(wall2.sprite);
		window.draw(wall3.sprite);
		window.draw(wall4.sprite);
		window.draw(graphics.backgroundTree);
		
// projectile enemy add 3/23
//start---------------------------------------------------------------------------------------------------------------
//Cuong 

// Projectile Vector Array
	vector<projectile>::const_iterator iter;
	vector<projectile> projectileArray;

// Projectile Object
	class projectile projectile1;
		
// Clock for projectile
		sf::Time elapsed1 = clock1.getElapsedTime();
		sf::Time elapsed2 = clock2.getElapsedTime();
		sf::Time elapsed3 = clock3.getElapsedTime();
		
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// Add Chasing AI 3/17
// Enemy Chasing (AI)
		counter = 0;
		for (iter4 = enemyArray.begin(); iter4 != enemyArray.end(); iter4++)
		{
			if (enemyArray[counter].chase == true)
			{
				if (elapsed3.asSeconds() >= 0.5) ////////////////////////changed to 0.5 on 04/01 
					//if (elapsed1.asSeconds() >= 1)
					
				{
					clock3.restart();
					

					int tempRand = generateRandom(3);

					/*if (tempRand == 1) // Enemy Fires Projectile at Player & Chases Player
					{
						projectile1.attackDamage = enemyArray[counter].attackDamage;
						cout << " enemy collision with player" << endl;						// Player to Right
						if ((player.body.getPosition().x < enemyArray[counter].rect.getPosition().x) && (abs(player.body.getPosition().y - enemyArray[counter].rect.getPosition().y) <= 40))
						{
							//soundShot.play();
							//projectile1.enemyProjectile = true;
							//projectile1.direction = 3;
							//projectile1.rect.setPosition(enemyArray[counter].rect.getPosition().x + enemyArray[counter].rect.getSize().x / 2 - projectile1.rect.getSize().x / 2, enemyArray[counter].rect.getPosition().y + enemyArray[counter].rect.getSize().y / 2 - projectile1.rect.getSize().y / 2);
							//projectileArray.push_back(projectile1);
							//projectile1.enemyProjectile = false;

							enemyArray[counter].direction = 3;
						}
						
						// Player to Left
						if ((player.body.getPosition().x > enemyArray[counter].rect.getPosition().x) && (abs(player.body.getPosition().y - enemyArray[counter].rect.getPosition().y) <= 40))
						{
							//soundShot.play();
							//projectile1.enemyProjectile = true;
							//projectile1.direction = 4;
							//projectile1.rect.setPosition(enemyArray[counter].rect.getPosition().x + enemyArray[counter].rect.getSize().x / 2 - projectile1.rect.getSize().x / 2, enemyArray[counter].rect.getPosition().y + enemyArray[counter].rect.getSize().y / 2 - projectile1.rect.getSize().y / 2);
							//projectileArray.push_back(projectile1);
							//projectile1.enemyProjectile = false;

							enemyArray[counter].direction = 4;
						}

						// Player to Top
						if ((player.body.getPosition().y < enemyArray[counter].rect.getPosition().y) && (abs(player.body.getPosition().x - enemyArray[counter].rect.getPosition().x) <= 40))
						{
							//soundShot.play();
							//projectile1.enemyProjectile = true;
							//projectile1.direction = 1;
							//projectile1.rect.setPosition(enemyArray[counter].rect.getPosition().x + enemyArray[counter].rect.getSize().x / 2 - projectile1.rect.getSize().x / 2, enemyArray[counter].rect.getPosition().y + enemyArray[counter].rect.getSize().y / 2 - projectile1.rect.getSize().y / 2);
							//projectileArray.push_back(projectile1);
							//projectile1.enemyProjectile = false;

							enemyArray[counter].direction = 1;
						}

						// Player to Bottom
						if ((player.body.getPosition().y > enemyArray[counter].rect.getPosition().y) && (abs(player.body.getPosition().x - enemyArray[counter].rect.getPosition().x) <= 40))
						{
							//soundShot.play();
							//projectile1.enemyProjectile = true;
							//projectile1.direction = 2;
							//projectile1.rect.setPosition(enemyArray[counter].rect.getPosition().x + enemyArray[counter].rect.getSize().x / 2 - projectile1.rect.getSize().x / 2, enemyArray[counter].rect.getPosition().y + enemyArray[counter].rect.getSize().y / 2 - projectile1.rect.getSize().y / 2);
							//projectileArray.push_back(projectile1);gun
							//projectile1.enemyProjectile = false;

							enemyArray[counter].direction = 2;
						}
					}*/
					//else if (tempRand == 2) // Enemy Chases Player
				 if (tempRand == 2) // Enemy Chases Player
					{
						if (player.body.getPosition().y < enemyArray[counter].rect.getPosition().y)
						{
							enemyArray[counter].direction = 1;
						}
						else if (player.body.getPosition().y > enemyArray[counter].rect.getPosition().y)
						{
							enemyArray[counter].direction = 2;
						}
						else if (player.body.getPosition().x < enemyArray[counter].rect.getPosition().x)
						{
							enemyArray[counter].direction = 3;
						}
						else if (player.body.getPosition().x > enemyArray[counter].rect.getPosition().x)
						{
							enemyArray[counter].direction = 4;
						}
					}
					else // Enemy Chases Player
					{
						if (player.body.getPosition().x < enemyArray[counter].rect.getPosition().x)
						{
							enemyArray[counter].direction = 3;
						}
						else if (player.body.getPosition().x > enemyArray[counter].rect.getPosition().x)
						{
							enemyArray[counter].direction = 4;
						}
						else if (player.body.getPosition().y < enemyArray[counter].rect.getPosition().y)
						{
							enemyArray[counter].direction = 1;
						}
						else if (player.body.getPosition().y > enemyArray[counter].rect.getPosition().y)
						{
							enemyArray[counter].direction = 2;
						}
					}

				}
			}

			counter++;
		}




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// Add 03/23
// Projectile Collides with Enemy
		counter = 0;
		for (iter = projectileArray.begin(); iter != projectileArray.end(); iter++)
		{
			counter2 = 0;
			for (iter4 = enemyArray.begin(); iter4 != enemyArray.end(); iter4++)
			{
			  if (projectileArray[counter].rect.getGlobalBounds().intersects(enemyArray[counter2].rect.getGlobalBounds()))
				{
					cout << "bullet collision with enemy" << endl;
					
					projectileArray[counter].destroy = true;

					enemyArray[counter2].hp -= projectileArray[counter].attackDamage;
					if (enemyArray[counter2].hp <= 0)
					{
						enemyArray[counter2].alive = false;
					}
					
					// Chasing
					enemyArray[counter2].chase = true;

				}

				counter2++;
			}

			counter++;
		}
      
// Delete Dead Enemy
		counter = 0;
		for (iter4 = enemyArray.begin(); iter4 != enemyArray.end(); iter4++)
		{
			if (enemyArray[counter].alive == false)
			{
				cout << "Enemy was killed" << endl;
				enemyArray.erase(iter4);
				break;
			}

			counter++;
		}
		
// Delete Projectile
		counter = 0;
		for (iter = projectileArray.begin(); iter != projectileArray.end(); iter++)
		{
			if (projectileArray[counter].destroy == true)
			{
				cout << "projectile deleted" << endl;
				projectileArray.erase(iter);
				break;
			}

			counter++;
		}

//--------------------------------------------------------------------------------------------------
//Cuong
// Projectile Collides with Enemy type 2 /////////////////////////////////////////added on 04/01
//start---------------------------------------------------------------------------------------
		counter = 0;
		for (iter = projectileArray.begin(); iter != projectileArray.end(); iter++)
		{
			counter2 = 0;
			for (iter4 = enemy1Array.begin(); iter4 != enemy1Array.end(); iter4++)
			{
				if (projectileArray[counter].rect.getGlobalBounds().intersects(enemy1Array[counter2].rect.getGlobalBounds()))
				{
					cout << "bullet collision with enemy" << endl;

					projectileArray[counter].destroy = true;

					enemy1Array[counter2].hp -= projectileArray[counter].attackDamage;
					if (enemy1Array[counter2].hp <= 0)
					{
						enemy1Array[counter2].alive = false;
					}

				}

				counter2++;
			}

			counter++;
		}

		// Delete Dead Enemy
		counter = 0;
		for (iter4 = enemy1Array.begin(); iter4 != enemy1Array.end(); iter4++)
		{
			if (enemy1Array[counter].alive == false)
			{
				cout << "Enemy was killed" << endl;
				enemy1Array.erase(iter4);
				break;
			}

			counter++;
		}

		
//end-------------------------------------------------------------------------------------------------------------
		

/////////////////////////////////////////////////////////////////////////////////////////////////////// Add 3/23
// Player Fires Shoot  (Space bar)

		if (elapsed1.asSeconds() >= 0.1)
		{
			clock1.restart();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				projectile1.rect.setPosition(player.body.getPosition().x + player.body.getSize().x / 2 - projectile1.rect.getSize().x / 2, player.body.getPosition().y + player.body.getSize().y / 2 - projectile1.rect.getSize().y / 2);
				projectile1.direction = player.direction;
				projectileArray.push_back(projectile1);
			}

		}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Draw Projectiles
		counter = 0;
		for (iter = projectileArray.begin(); iter != projectileArray.end(); iter++)
		{
			projectileArray[counter].update(); // Update Projectile
			window.draw(projectileArray[counter].rect);

			counter++;
		}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////		
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

//Cuong 
// Draw Enemies type 2 no chasing - spawn randomly ///////////////////////////////////// added on 04/01
		counter = 0;
		for (iter4 = enemy1Array.begin(); iter4 != enemy1Array.end(); iter4++)
		{
			enemy1Array[counter].update();
			enemy1Array[counter].updateMovement();
			//window.draw(enemyArray[counter].rect);
			window.draw(enemy1Array[counter].sprite);

			counter++;
		}
//---------------------------------------------------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Miguel Draw Resources
		counter = 0;
		for (resourceit = resourceArray.begin(); resourceit != resourceArray.end(); resourceit++)
		{
			resourceArray[counter].update();

			window.draw(resourceArray[counter].rect);
			window.draw(resourceArray[counter].sprite);
			counter++;
		}
//---------------------------------------------------------------------------------------------------------------
//Miguel Draw Resources
		counter = 0;
		for (resourceit = resourceArray.begin(); resourceit != resourceArray.end(); resourceit++)
		{
			resourceArray[counter].update();

			window.draw(resourceArray[counter].rect);
			window.draw(resourceArray[counter].sprite);
			counter++;
		}

		window.draw(text);
		help == 0 ? window.draw(textHelp) : window.draw(textHelp2);
		//Miguel draw text
		window.draw(text);
		help == 0 ? window.draw(textHelp) : window.draw(textHelp2);

		window.draw(tower1);
		window.draw(tower2);
		window.draw(tower3);

//---------------------------------------------------------------------------------------------------------------

		//displaying Escape Menu
		if (exitgame == 1) window.draw(graphics.menuImage);
		else	graphics.menuImage.setTexture(&graphics.menuTexture);
 
	
		window.display();
	}

		return 0;
}



