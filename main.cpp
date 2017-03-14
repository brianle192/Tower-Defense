#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Animation.h"
#include "Player.h"
#include "Audio.h"
#include "Graphic.h"
#include "enemy.h"

using namespace std;
int exitgame = 0;

int main()
{
	int counter = 0;
	
	sf::RenderWindow window(sf::VideoMode(720, 480), "Fight Hard Yeah! Tower Defense Game", sf::Style::Close | sf::Style::Resize);
	Audio audio;
	Graphic graphics;
	int flag = 0;

	
	//Player character texture, rectangle bound to box
	sf::Texture playerTexture;
	playerTexture.loadFromFile("char_sprite_walk_swords.png");
	Player player(&playerTexture, sf::Vector2u(3, 3), 0.3f, 100.0f);

	
	//Assigning Player Footstep Sounds
	if (!player.soundBuf.loadFromFile("foot.wav"))
		std::cout << "can't open sound file" << std::endl;
	player.sound.setBuffer(player.soundBuf);
	player.sound.setVolume(100);

	//////////////////////////////////////////////////////////////////////////
	// Adding enemy texture - Not finish yet, need to work more
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


	////////////////////////////////////////////////////////////////////
	// Enemy Vector Array
	vector<enemy>::const_iterator iter4;
	vector<enemy> enemyArray;

	// Enemy Object - make 10 enemies
	class enemy enemy1;
	enemy1.sprite.setTexture(textureEnemy);
	//enemy1.sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	enemy1.rect.setPosition(700, 200);
	enemyArray.push_back(enemy1);
	enemy1.rect.setPosition(500, 200);
	enemyArray.push_back(enemy1);
	enemy1.rect.setPosition(400, 200);
	enemyArray.push_back(enemy1);
	enemy1.rect.setPosition(300, 200);
	enemyArray.push_back(enemy1);
	enemy1.rect.setPosition(200, 200);
	enemyArray.push_back(enemy1);
	enemy1.rect.setPosition(100, 200);
	enemyArray.push_back(enemy1); 
	enemy1.rect.setPosition(100, 100);
	enemyArray.push_back(enemy1);
	enemy1.rect.setPosition(100, 300);
	enemyArray.push_back(enemy1);
	enemy1.rect.setPosition(100, 400);
	enemyArray.push_back(enemy1);
	enemy1.rect.setPosition(100, 500);
	enemyArray.push_back(enemy1);
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
		player.Update(deltaTime);
		// Draw the sprite
		window.clear(sf::Color(125, 125, 125));
		window.draw(graphics.background);
		window.draw(graphics.background2);
		window.draw(graphics.background3);
		window.draw(graphics.background4);
		window.draw(graphics.background5);
		player.Draw(window);
		window.draw(graphics.backgroundTree);


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



