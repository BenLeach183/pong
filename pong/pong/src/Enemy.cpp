#include "Enemy.h"

Enemy::Enemy(sf::RenderWindow& window, Ball &ball, Paddle &enemyPaddle)
	// initialise the objects
	: m_window(window),
	m_ball(ball),
	m_enemyPaddle(enemyPaddle)
{}

// calculate target position to move to
void Enemy::updateTarget() {
	// get distance from ball to paddle
	// x and y velocity are the same -> distance horizontally to screen
	// is same as distance it will move vertically before it is at same x as paddle.
	float fXOffset = m_enemyPaddle.getShape().getPosition().x - m_ball.getPosition().x;

	// if ball is moving down flip offset to negative
	(m_ball.getVelocity().y < 0) ? fXOffset *= -1 : fXOffset *= 1;

	// add the offset to the balls position, this is the position ball would hit exactly if it didn't hit the ceiling or floor
	m_target = m_ball.getPosition().y + fXOffset;

	// add a random range between -120 to 120 to the range
	m_target += (rand() % 240) - 120;

	// clamp the values to the screen size
	if (m_target < 0) m_target = 0;
	if (m_target > m_window.getSize().y) m_target = m_window.getSize().y;
}

// move the paddle
void Enemy::move(float dt) {
	// vall the paddle move function and move towards the target position
	m_enemyPaddle.move(dt, m_target);
}