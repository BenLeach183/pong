#include "Ball.h"
#include <iostream>

Ball::Ball(sf::Vector2f position, float radius, float speed, sf::Color color)
{
	// initialise the ball with constructor values
	m_speed = speed;
	m_velocity.x = speed;
	m_velocity.y = speed;
	m_shape.setRadius(radius);
	m_shape.setPosition(position);
	m_shape.setFillColor(color);
	m_shape.setOrigin(m_shape.getRadius() / 2, m_shape.getRadius() / 2);
}

// draw the circle shape to the window parameter
void Ball::draw(sf::RenderWindow& window)
{
	window.draw(m_shape);
}

// overload the draw function to take in render texture instead
void Ball::draw(sf::RenderTexture& renderTexture)
{
	renderTexture.draw(m_shape);
}

// move the ball
void Ball::move(float dt, sf::RenderWindow& window)
{
	// move the circle in direction of velocity
	m_shape.move(m_velocity * dt);

	// if the ball goes past the border, and then flips direction, and its still past the border
	// it will flip again, and become stuck in a never ending loop
	// 
	//if (m_shape.getPosition().y < 1 ||
	//	m_shape.getPosition().y + m_shape.getRadius() * 2 > window.getSize().y - 1)
	//	m_velocity.y = -m_velocity.y;
	//
	// instead I just change the sign based on which wall it hits
	if (m_shape.getPosition().y < 1) m_velocity.y = m_speed;
	if (m_shape.getPosition().y + getRadius() * 2 > window.getSize().y - 1) m_velocity.y = - m_speed;
}

// get the current position of the ball
sf::Vector2f Ball::getPosition()
{
	return m_shape.getPosition();
}

// set the position of the ball
void Ball::setPosition(float x, float y)
{
	m_shape.setPosition(x, y);
}

// update the velocity
void Ball::updateVelocity(float val)
{
	// multiply the speed by a value, negative is left, positive is right
	m_velocity.x = m_speed * val;
}

// get current velocity
sf::Vector2f Ball::getVelocity() {
	return m_velocity;
}

// set the speed of the ball
void Ball::setSpeed(float m_speed) {
	// to maintain direction first divide by current speed value before multiplying by new
	m_velocity.x = (m_velocity.x / this->m_speed) * m_speed;
	m_velocity.y = (m_velocity.y / this->m_speed) * m_speed;

	// update current speed
	this->m_speed = m_speed;
}

// get the current speed value
float Ball::getSpeed() {
	return m_speed;
}

// get the circle shape object
sf::CircleShape Ball::getShape()
{
	return m_shape;
}

// get the fill color
sf::Color Ball::getColor() {
	return m_shape.getFillColor();
}

// set the fill color
void Ball::setColor(sf::Color color) {
	m_shape.setFillColor(color);
}

// get the bounds of the shape, used for intersect checks
sf::FloatRect Ball::getBounds() const
{
	return m_shape.getGlobalBounds();
}

// get the radius of the circle
float Ball::getRadius() {
	return m_shape.getRadius();
}
