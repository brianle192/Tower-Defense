#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Animation.h"
#include "Player.h"
#include "Audio.h"
#include "Graphic.h"
#include "enemy.h"
#include "Wall.h"
//----------------------------- add on 03/23
#include "projectile.h"
#include "random.h"
#include "entity.h"

using namespace std;
int exitgame = 0;

int main()
{
	sf::Clock clock1; // clock for AI
//----------------------------- add on 03/23
	sf::Clock clock2;
	sf::Clock clock3;
	
	sf::RenderWindow window(sf::VideoMode(720, 480), "Fight Hard Yeah! Tower Defense Game", sf::Style::Close | sf::Style::Resize);
	Audio audio;
	Graphic graphics;
	int flag = 0, counter = 0;
	int counter2 = 0;
	int counter3 = 0;
	
	//Player character texture, rectangle bound to box
	sf::Texture playerTexture;
	playerTexture.loadFromFile("char_sprite_walk_swords.png");

	
   ///////////////////////////////////////////////////// Add 3/15
	// Wall creation
	vector<Wall>::const_iterator wallit;
	vector<Wall> wallArray;

	/*class Wall wall1;
	sf::Texture textureWall;
	textureWall.loadFromFile("wall.jpg");
	wall1.rect.setTexture(&textureWall);
	*/

	class Wall wall1, wall2, wall3;
	sf::Texture textureWall;
	//textureWall.loadFromFile("cave_top.png");
	wall1.rect.setTexture(&textureWall);
	sf::Texture textureWall2;
	//textureWall2.loadFromFile("cave_bottom_left.png");
	wall2.rect.setTexture(&textureWall2);
	sf::Texture textureWall3;
	//textureWall3.loadFromFile("cave_bottom_right.png");
	wall3.rect.setTexture(&textureWall3);

	wall1.rect.setPosition(0, 0);
	wall1.rect.setSize(sf::Vector2f(720, 200));
	wallArray.push_back(wall1);

	wall2.rect.setPosition(0, 330);
	wall2.rect.setSize(sf::Vector2f(150, 150));
	wallArray.push_back(wall2);

	wall3.rect.setPosition(150, 430);
	wall3.rect.setSize(sf::Vector2f(570, 50));
	wallArray.push_back(wall3);
	//////////////////////////////////////////////////////////////

	Player player(&playerTexture, sf::Vector2u(3, 3), 0.3f, 100.0f);

	
	
	//Assigning Player Footstep Sounds
	if (!player.soundBuf.loadFromFile("foot.wav"))
		std::cout << "can't open sound file" << std::endl;
	player.sound.setBuffer(player.soundBuf);
	player.sound.setVolume(100);

	//////////////////////////////////////////////////////////////////////////
	// Adding enemy texture - need to work more for sprite sheet
	sf::Texture textureEnemy;
	if (!textureEnemy.loadFromFile("ghost.png")) {
		return EXIT_FAILURE;
	}
	

	//Menu
	sf::RectangleShape menuImage(sf::Vector2f(720.0f, 480.0f));
	menuImage.setPosition(0.0f, 0.0f);
	sf::Texture menuTexture;
	menuTexture.loadFromFile("menu_1.png");
	menuImage.setTexture(&menuTexture);

	//Clock for sprite rotation
	float deltaTime = 0.0f;
	sf::Clock clock;

	//Playing Background Music
	cout << "Playing background music" << endl;
	audio.backgroundmusic1.play();
	audio.backgroundmusic1.setVolume(25);

//------------------------------------------------------------------ add on 03/23
	// Projectile Vector Array
	vector<projectile>::const_iterator iter;
	vector<projectile> projectileArray;

	// Projectile Object
	class projectile projectile1;
//------------------------------------------------------------------------------------	
	////////////////////////////////////////////////////////////////////
	// Enemy Vector Array
	vector<enemy>::const_iterator iter4;
	vector<enemy> enemyArray;

	// Enemy Objects - make 2 enemies try
	class enemy enemy1, enemy2;
	enemy1.sprite.setTexture(textureEnemy);
	enemy1.rect.setPosition(700, 250); // y: 200 is the border with the wall
	enemyArray.push_back(enemy1);
	
	enemy2.sprite.setTexture(textureEnemy);
	enemy2.rect.setPosition(500, 260);
	enemyArray.push_back(enemy2);

/////////////////////////////////////////////////////////////////////


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
					std::cout << "Menu Being Displayed" << std::endl;
					if (exitgame == 0)
						exitgame = 1;
					else
						exitgame = 0;
				}
			}
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
			playerTexture.loadFromFile("char_sprite_walk_swords.png");
			
		}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// Add 3/16
		//Enemy Wall Collision
		counter = 0;
		for (iter4 = enemyArray.begin(); iter4 != enemyArray.end(); iter4++)
		{
			int counter2 = 0;
			for (wallit = wallArray.begin(); wallit != wallArray.end(); wallit++)
			{
				if (enemyArray[counter].rect.getGlobalBounds().intersects(wallArray[counter2].rect.getGlobalBounds()))
				{	
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////// Add 3/16
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
		
/////////////////////////////////////////////////////////////////////////////////

		window.setView(player.view);
		

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


///////////////////////////////////////////// Add 3/16

		player.Draw(window);

		

		window.draw(wall1.sprite);
		window.draw(wall2.sprite);
		window.draw(wall3.sprite);

		window.draw(graphics.backgroundTree);

		//displaying Escape Menu
		if (exitgame == 1)
			window.draw(menuImage);
		else
			menuImage.setTexture(&menuTexture);

	//////////////////////////////////////////////////////////////////////////////////////////	

		sf::Time elapsed1 = clock1.getElapsedTime();
	//---------------------------------------------------------------------- add on 03/23	
		sf::Time elapsed2 = clock2.getElapsedTime();
		sf::Time elapsed3 = clock3.getElapsedTime();
	
	//////////////////////////////////////////////////////////////////////////////////////////
		// Enemy Chasing (AI)
		counter = 0;
		for (iter4 = enemyArray.begin(); iter4 != enemyArray.end(); iter4++)
		{
			if (enemyArray[counter].chase == true)
			{
				if (elapsed3.asSeconds() >= 1)
					
				{
					clock3.restart();

					int tempRand = generateRandom(3);
		         
					if (tempRand == 1) // Track Player Position
					{
						// Player to Right
						if ((player.body.getPosition().x < enemyArray[counter].rect.getPosition().x) && (abs(player.body.getPosition().y - enemyArray[counter].rect.getPosition().y) <= 40))
							{ 
							enemyArray[counter].direction = 3;
							}
						// Player to Left
						if ((player.body.getPosition().x > enemyArray[counter].rect.getPosition().x) && (abs(player.body.getPosition().y - enemyArray[counter].rect.getPosition().y) <= 40))
							{
							enemyArray[counter].direction = 4;
							}
						// Player to Top
						if ((player.body.getPosition().y < enemyArray[counter].rect.getPosition().y) && (abs(player.body.getPosition().x - enemyArray[counter].rect.getPosition().x) <= 40))
							{ 
							enemyArray[counter].direction = 1;
							}
						// Player to Bottom
						if ((player.body.getPosition().y > enemyArray[counter].rect.getPosition().y) && (abs(player.body.getPosition().x - enemyArray[counter].rect.getPosition().x) <= 40))
							{
							enemyArray[counter].direction = 2;
							}
					}
					else if (tempRand == 2) // Enemy Chases Player
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
	// Chasing boolean 
         //enemyArray[counter2].chase = true; // changed on 03/23
		
//------------------------------------------------------------------------------------------------------------
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

		// Draw Projectiles
		counter = 0;
		for (iter = projectileArray.begin(); iter != projectileArray.end(); iter++)
		{
			projectileArray[counter].update(); // Update Projectile
			window.draw(projectileArray[counter].rect);

			counter++;
		}
		
	//-----------------------------------------------------------------------------------------------------------------------------	
	////////////////////////////////////////////////////////////////////////////////////////////		
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
  /////////////////////////////////////////////////////////////////////////////////////////////
		window.display();
	}

		return 0;
}



