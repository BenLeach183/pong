#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "TextureHandler.h"

class Paddle
{
private:
	// variable for movement speed of paddle
	float m_speed = 400.f;

	// 2d vector for paddle size
	sf::Vector2f m_size;

	// sfml rectangle shape
	sf::RectangleShape m_shape;

	// store the texture and the sprite that will be rendered
	sf::Texture m_paddleTex;
	sf::Sprite m_sprite;
public:
	// constructor
	Paddle(sf::Vector2f position, float width, float height, std::string sTexFilename);

	// overloaded draw function so paddle can be drawn to render texture as well
	void draw(sf::RenderWindow& window);
	void draw(sf::RenderTexture& renderTexture);

	// move function takes delta time and a y position to move towards over time
	void move(float dt, float windowYVal);

	// set the x position of the paddle, if window gets resized
	void setHorizontalPosition(float horizontalPosition);

	// get the bounds and shape of rectangle
	sf::FloatRect getBounds() const;
	sf::RectangleShape getShape();

	// set and get the movement speed of the paddle
	void setSpeed(float speed);
	float getSpeed();
};

