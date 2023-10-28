#pragma once
#include <string>
#include "TextureHandler.h"
#include <SFML/Graphics.hpp>

class PowerUp_Base
{
private:
	// flag for if the power up is currently enabled
	bool m_activated = false;

	// store the texture for the power up
	sf::Texture m_Texture;
public:
	// retrieve the texture
	sf::Texture getTexture();
	// set the texture based on a filename
	void setTexture(std::string sFilename);

	// set and get if the power up is active
	bool getActive();
	void setActive(bool active);

	// virtual functions for the classes to implement, enables and disables the power up
	// update runs every tick
	virtual void enable() = 0;
	virtual void disable() = 0;
	virtual void update() = 0;
};

