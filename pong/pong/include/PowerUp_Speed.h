#pragma once
#include "PowerUp_Base.h"
#include "Paddle.h"
#include "Ball.h"
#include <SFML/Audio.hpp>

class PowerUp_Speed : public PowerUp_Base
{
private:
	// store reference to the paddle and the ball
	Paddle* m_paddle;
	Ball* m_ball;
	// store reference to the background music
	sf::Music* m_music;

	// store the default values - these get copied into when effect is enabled
	float m_defaultPaddleSpeed = 800.f;
	float m_defaultBallSpeed = 400.f;
	sf::Color m_defaultBallColor = sf::Color(255, 255, 255, 255);

	// variable to create a new ball color
	sf::Color m_ballColor = sf::Color(0, 0, 0, 255);

	// target values to interplate to
	float m_targetPaddleSpeed;
	float m_targetBallSpeed;
	sf::Color m_targetBallColor = sf::Color(255, 51, 0, 255);

	// clock to fade in/out the effect
	sf::Clock m_fadeClock;

	// functions for linear interpolation
	sf::Color lerp(sf::Color start, sf::Color end, float t);
	sf::Uint8 lerp(sf::Uint8 start, sf::Uint8 end, float t);
	float lerp(float start, float end, float t);
public:
	// constructor
	PowerUp_Speed(Paddle& m_paddle, Ball& m_ball, sf::Music& music);

	// declarations for the virtual functions
	void enable();
	void disable();
	void update();
};

