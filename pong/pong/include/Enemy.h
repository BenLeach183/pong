#pragma once
#include <SFML/Graphics.hpp>
#include "Paddle.h"
#include "Ball.h"

class Enemy
{
private:
	// references to the ball and the paddle under control of the ai
	Ball& m_ball;
	Paddle& m_enemyPaddle;

	// the target y position for the paddle to move to
	float m_target = 0.0f;

	// reference to the render window
	sf::RenderWindow& m_window;
public:
	// constructor
	Enemy(sf::RenderWindow& window, Ball& ball, Paddle& enemyPaddle);

	// calculate the target position
	void updateTarget();

	// move the paddle towards target over time
	void move(float dt);
};