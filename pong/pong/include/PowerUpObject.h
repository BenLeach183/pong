#pragma once
#include <vector>
#include "PowerUp_Base.h"
#include "PowerUp_Drunk.h"
#include "PowerUp_Speed.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class PowerUpObject
{
private:
	// flags to track if graphics and collision are enabled on the powerup
	bool m_isGraphicEnabled = false;
	bool m_isCollisionEnabled = false;

	// true if the power up is currently being animated
	bool m_animate = false;

	// vector to store reference to each pwoer up type
	std::vector<PowerUp_Base*> PowerUps;

	// size of power up
	sf::Vector2f m_size;

	// shape and sprite
	sf::RectangleShape m_shape;
	sf::Sprite m_sprite;

	// default texture of the question mark power up
	sf::Texture m_DefaultTexture;

	// current texture
	sf::Texture m_Texture;

	// number of frames in the animation
	static const int m_numFrames = 10;

	// current frame
	int m_currentFrame = 0;

	// width and height of each frame
	int m_TexWidth = 16, m_TexHeight = 16;

	// array of IntRects storing coordinates and size of each frame
	sf::IntRect powerUpRects[m_numFrames];

	// clock to animate the sprite
	sf::Clock m_animClock;
public:
	// enum to store each type of power up, "Count" gives me a value for number of elements in the enum
	enum PowerUpTypes { Drunk, Speed, Count };

	// the power up type for this power up
	PowerUpTypes powerType;

	// constructor
	PowerUpObject(PowerUpTypes powerType, sf::Vector2f position, float width, float height, std::string sTexFilename, sf::Shader &shader, Paddle& paddle, Ball& ball, sf::Music& music);

	// overloaded draw function so paddle can be drawn to render texture as well
	void draw(sf::RenderWindow& window, sf::Shader* shader);
	void draw(sf::RenderTexture& renderTexture, sf::Shader* shader);

	// called every tick, calls update function on each power up
	void update();

	// enables the current power up
	void enable();

	// disables the current power up
	void disable();

	// deletes all the objects created using new keyword
	void deleteObjects();

	// set the position of the power up
	void setPosition(sf::Vector2f position);

	// returns if the power collision is enabled
	bool getEnabled();

	// sets the power up type to a random type
	void setType();

	// enables the collision and graphics of the power up
	void setEnabled(bool isEnabled);

	// gets the bounds for the rectangle
	sf::FloatRect getBounds() const;

	// called when the ball collides with the power up
	void hit();

	// animates the power up
	void animate();
};

