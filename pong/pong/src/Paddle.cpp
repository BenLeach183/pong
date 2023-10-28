#include "Paddle.h"

Paddle::Paddle(sf::Vector2f position, float width, float height, std::string sTexFilename)
{
	// intialise the paddle with constructor values
	m_size.x = width;
	m_size.y = height;
	m_shape.setSize(m_size);
	m_shape.setOrigin(m_shape.getSize() / 2.f);

	// set the sprite position to the same as the shape
	m_shape.setPosition(position);
	m_sprite.setPosition(position);

	// load the texture onto the sprite from the texture handler class
	TextureHandler::loadTexture(m_paddleTex, m_sprite, sTexFilename, m_size);
}

// draw the paddle textured sprite to the window parameter
void Paddle::draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

// overload the draw function to take in render texture instead
void Paddle::draw(sf::RenderTexture& renderTexture)
{
	renderTexture.draw(m_sprite);
}

// move the paddle towards a y position
void Paddle::move(float dt, float windowYVal)
{
	// check if the bottom of the paddle is above the point to move to
	if (m_shape.getPosition().y - m_shape.getSize().y / 2 > windowYVal)
		// if so move down
		m_shape.move(0, -m_speed * dt);

	// check if the top of the paddle is below the point to move to
	if (m_shape.getPosition().y + m_shape.getSize().y / 2 < windowYVal)
		// if so move up
		m_shape.move(0, m_speed * dt);

	// copy the shapes position to the textured sprite
	m_sprite.setPosition(m_shape.getPosition());
}

// get the brounds of the rectangle
sf::FloatRect Paddle::getBounds() const
{
	return m_shape.getGlobalBounds();
}

// get the rectangle shape object
sf::RectangleShape Paddle::getShape()
{
	return m_shape;
}

// set the paddle movement speed
void Paddle::setSpeed(float speed)
{
	m_speed = speed;
}

// get the paddle movement speed
float Paddle::getSpeed() {
	return m_speed;
}

// set the x position of the paddle
void Paddle::setHorizontalPosition(float horizontalPosition) {
	// set the position for shape and sprite
	m_shape.setPosition(sf::Vector2f(horizontalPosition, m_shape.getPosition().y));
	m_sprite.setPosition(sf::Vector2f(horizontalPosition, m_shape.getPosition().y));
}