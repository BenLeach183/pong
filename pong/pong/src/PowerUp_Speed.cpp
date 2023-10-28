#include "PowerUp_Speed.h"

PowerUp_Speed::PowerUp_Speed(Paddle& paddle, Ball& ball, sf::Music& music) {
	// set the texture to the filename "speed.png"
	setTexture("speed.png");

	// store the references
	m_paddle = &paddle;
	m_ball = &ball;
	m_music = &music;
}

// enable the effect
void PowerUp_Speed::enable() {
	// initialise the default values
	m_defaultBallSpeed = m_ball->getSpeed();
	m_defaultPaddleSpeed = m_paddle->getSpeed();
	m_defaultBallColor = m_ball->getColor();

	// calculate the target values for speed increase
	m_targetBallSpeed = m_defaultBallSpeed * 1.4f;
	m_targetPaddleSpeed = m_defaultPaddleSpeed * 1.4f;

	// set the effect to active and restart fade clock
	setActive(true);
	m_fadeClock.restart();
}

// disable the effect
void PowerUp_Speed::disable() {
	// set the active flag to false
	setActive(false);

	// set the values back to their default
	m_ball->setSpeed(m_defaultBallSpeed);
	m_paddle->setSpeed(m_defaultPaddleSpeed);
	m_ball->setColor(m_defaultBallColor);

	// set the music pitch back to the default of 1
	m_music->setPitch(1.0f);
}

void PowerUp_Speed::update() {
	// if the effect isn't active return
	if (!getActive()) return;

	// calculate the elapsed time
	float elapsedTime = m_fadeClock.getElapsedTime().asSeconds();

	// fade in for the first 3 seconds
	if (elapsedTime < 3) {
		// calculate t, value between 0-1 for the first 3 seconds
		float t = elapsedTime / 3;

		// lerp the ball colour, ball speed, paddle speed and music pitch towards target
		m_ballColor = lerp(m_defaultBallColor, m_targetBallColor, t);
		m_ball->setSpeed(lerp(m_defaultBallSpeed , m_targetBallSpeed, t));
		m_paddle->setSpeed(lerp(m_defaultPaddleSpeed, m_targetPaddleSpeed, t));
		m_music->setPitch(lerp(1.0f, 1.4f, t));
	}

	// fade out for last 3 seconds
	if (elapsedTime > 13 && elapsedTime < 16) {
		// calculate t, value between 1-0 for the last 3 seconds
		float t = (16 - elapsedTime) / 3;

		// lerp the ball colour, ball speed, paddle speed and music pitch towards default
		m_ballColor = lerp(m_defaultBallColor, m_targetBallColor, t);
		m_ball->setSpeed(lerp(m_defaultBallSpeed, m_targetBallSpeed, t));
		m_paddle->setSpeed(lerp(m_defaultPaddleSpeed, m_targetPaddleSpeed, t));
		m_music->setPitch(lerp(1.0f, 1.4f, t));
	}

	// set the ball colour
	m_ball->setColor(m_ballColor);

	// at 16 seconds disable the effect
	if (elapsedTime >= 16) {
		disable();
	}
}

// use the formula  start * (1 - t) + end * t
// to calculate the lerp
sf::Color PowerUp_Speed::lerp(sf::Color start, sf::Color end, float t) {
	sf::Color col;
	col.r = lerp(start.r, end.r, t);
	col.g = lerp(start.g, end.g, t);
	col.b = lerp(start.b, end.b, t);

	return col;
}

sf::Uint8 PowerUp_Speed::lerp(sf::Uint8 start, sf::Uint8 end, float t) {
	return start* (1 - t) + end * t;
}

float PowerUp_Speed::lerp(float start, float end, float t) {
	return start* (1.0f - t) + end * t;
}