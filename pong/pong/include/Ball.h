#pragma once
#include <SFML/Graphics.hpp>

class Ball
{
private:
	// store the speed and velocity
	float m_speed;
	sf::Vector2f m_velocity;

	// sfml circle shape
	sf::CircleShape m_shape;
public:
	Ball(sf::Vector2f position, float radius, float speed, sf::Color color);

	// overloaded draw function so ball can be drawn to render texture as well
	void draw(sf::RenderWindow& window);
	void draw(sf::RenderTexture& renderTexture);

	// move takes a delta time, and the window
	void move(float dt, sf::RenderWindow& window);

	// get and set position
	sf::Vector2f getPosition();
	void setPosition(float x, float y);

	// get the shape properties
	sf::CircleShape getShape();
	sf::FloatRect getBounds() const;
	float getRadius();

	// set and get velocity
	void updateVelocity(float val);
	sf::Vector2f getVelocity();

	// set and get speed
	void setSpeed(float m_speed);
	float getSpeed();

	// set and get ball colour
	sf::Color getColor();
	void setColor(sf::Color color);
};

