#include "PowerUpObject.h"

PowerUpObject::PowerUpObject(PowerUpTypes powerType, sf::Vector2f position, float width, float height, std::string sTexFilename, sf::Shader &shader, Paddle &paddle, Ball &ball, sf::Music &music) {
	// initialise the variables with constructor values
	this->powerType = powerType;

	m_size.x = width;
	m_size.y = height;
	m_shape.setSize(m_size);
	m_shape.setPosition(position);
	m_shape.setOrigin(m_shape.getSize() / 2.f);

	// set sprite to same position as shape
	m_sprite.setPosition(position);

	// add the power up classes to the vector
	PowerUps.push_back(new PowerUp_Drunk(shader, music));
	PowerUps.push_back(new PowerUp_Speed(paddle, ball, music));

	// load the animated texture, takes extra arguments for width and height of individual frame and num of frames
	TextureHandler::loadTexture(m_Texture, m_sprite, sTexFilename, m_size, m_TexWidth, m_TexHeight, m_numFrames);

	// set the default texture to the loaded animation texture
	m_DefaultTexture = m_Texture;

	// loop over the IntRect's array and load it with the position and size of each frame
	for (int i = 0; i < m_numFrames; i++)
	{
		powerUpRects[i] = sf::IntRect(0, i * m_TexHeight, m_TexWidth, m_TexHeight);
	}
}

// called each tick
void PowerUpObject::update() {
	// if animate is set to true, call the animate function
	if (m_animate) animate();

	// run the update function on each power up
	for (int i = 0; i < PowerUps.size(); i++)
	{
		PowerUps[i]->update();
	}
}

// draw the power up textured sprite to the window parameter, takes a shader to make the power up change colour
void PowerUpObject::draw(sf::RenderWindow& window, sf::Shader* shader)
{
	// if graphics is disabled don't render
	if(m_isGraphicEnabled) window.draw(m_sprite, shader);
}

// overload the draw function to take in render texture instead
void PowerUpObject::draw(sf::RenderTexture& renderTexture, sf::Shader* shader)
{
	// if graphics is disabled don't render
	if (m_isGraphicEnabled) renderTexture.draw(m_sprite, shader);
}

// enable the current power up
void PowerUpObject::enable() {
	PowerUps[(int)powerType]->enable();
}

// disable the current power up
void PowerUpObject::disable() {
	PowerUps[(int)powerType]->disable();
}

// loop over each pwoer up class and delete it, start from the back to the front
void PowerUpObject::deleteObjects() {
	for (int i = PowerUps.size() -1; i > 0; i--)
	{
		delete PowerUps[i];
	}
}

// enable the graphics and collision
void PowerUpObject::setEnabled(bool isEnabled) {
	m_isGraphicEnabled = isEnabled;
	m_isCollisionEnabled = isEnabled;
}

// return of collision is currently enabled on the power up
bool PowerUpObject::getEnabled() {
	return m_isCollisionEnabled;
}

// set the power up type to a random power up from the enum
void PowerUpObject::setType() {
	powerType = (PowerUpTypes) (rand() % (int)PowerUpTypes::Count);
}

// set the position of the shape and sprite of the power up
void PowerUpObject::setPosition(sf::Vector2f position) {
	m_shape.setPosition(position);
	m_sprite.setPosition(position);
}

// return the bounds of the rectangle
sf::FloatRect PowerUpObject::getBounds() const
{
	return m_shape.getGlobalBounds();
}

void PowerUpObject::hit() {
	// Only allow hit to be triggered once
	if (!m_isCollisionEnabled) return;
	m_isCollisionEnabled = false;

	// triggers the animation to start
	m_animate = true;
	// restart the animation clock
	m_animClock.restart();

	// enables the power up
	enable();
}

// animate the power up
void PowerUpObject::animate() {
	// if the animation is over
	if (m_currentFrame >= m_numFrames) {
		// set the texture to the specific power up texture
		m_Texture = PowerUps[(int)powerType]->getTexture();
		// set the sprite texture rect back to (0, 0) to display the texture
		m_sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));

		// after 1 second of displaying the new texture
		if (m_animClock.getElapsedTime().asSeconds() >= 1.0) {
			// set the texture back to the default question mark
			m_Texture = m_DefaultTexture;
			// disable the animation
			m_animate = false;
			// disable the graphics
			setEnabled(false);
			// set the animation frame back to 0
			m_currentFrame = 0;
		}
		return;
	}

	// if animation is not over, every 1/20 of a second
	if (m_animClock.getElapsedTime().asSeconds() >= 1.0 / 20) {
		// restart the clock
		m_animClock.restart();

		// increase the frame of the animation by 1
		m_currentFrame++;
		// set the sprite texture to new frame
		m_sprite.setTextureRect(powerUpRects[m_currentFrame]);
	}
}