#include "Audio.h"

Audio::Audio()
{

	if (!gunSoundBuffer.loadFromFile("gunshot.wav"))
		std::cout << "Unable to load gunshot" << std::endl;
	gunSound.setBuffer(gunSoundBuffer);
	gunSound.setVolume(100);

	if (!gunEmptySoundBuffer.loadFromFile("gunEmpty.wav"))
		std::cout << "Unable to load gun empty" << std::endl;
	gunEmptySound.setBuffer(gunEmptySoundBuffer);
	gunEmptySound.setVolume(100);

	if (!gunPickupBuffer.loadFromFile("gunload.wav"))
		std::cout << "Unable to load gun pickup" << std::endl;
	gunPickupSound.setBuffer(gunPickupBuffer);
	gunPickupSound.setVolume(80);

	if (!enemyDeathBuffer.loadFromFile("death.wav"))
		std::cout << "Unable to load death sound" << std::endl;
	enemyDeath.setBuffer(enemyDeathBuffer);
	enemyDeath.setVolume(80);

	//Loading in sound for Background Music
	if (!backgroundmusic1.openFromFile("silent_hill.wav"))
		std::cout << "Unable to load Music" << std::endl;

}



Audio::~Audio()
{
}
