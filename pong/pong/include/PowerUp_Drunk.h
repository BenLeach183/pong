#pragma once
#include "PowerUp_Base.h"
#include <SFML/Audio.hpp>

class PowerUp_Drunk : public PowerUp_Base
{
private:
	// store reference to the drunk shader
	sf::Shader* m_shader;
	// store reference to the background music
	sf::Music* m_music;

	// clock to fade in/out the effect
	sf::Clock m_fadeClock;
public:
	// constructor
	PowerUp_Drunk(sf::Shader& shader, sf::Music& music);

	// declarations for the virtual functions
	void enable();
	void disable();
	void update();
};

