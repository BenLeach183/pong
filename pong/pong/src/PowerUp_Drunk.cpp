#include "PowerUp_Drunk.h"

PowerUp_Drunk::PowerUp_Drunk(sf::Shader &shader, sf::Music &music) {
	// set the texture to the filename "drunk.png"
	setTexture("drunk.png");

	// store the references
	m_shader = &shader;
	m_music = &music;
}

// enable the effect
void PowerUp_Drunk::enable() {
	// set the uniform variable in the shader called drunk to true
	m_shader->setUniform("drunk", true);

	// restart the clock to fade in the effect
	m_fadeClock.restart();

	// set the effect to active
	setActive(true);
}

// disable the effect
void PowerUp_Drunk::disable() {
	// set the uniform variable in the shader to false
	m_shader->setUniform("drunk", false);

	// set the active flag to false
	setActive(false);

	// set the music pitch back to 1
	m_music->setPitch(1.0f);
}

void PowerUp_Drunk::update() {
	// if the effect isn't active return
	if (!getActive()) return;

	// calculate the elapsed time
	float elapsedTime = m_fadeClock.getElapsedTime().asSeconds();

	// fade in for the first 5 seconds
	if (elapsedTime < 5) {
		// increase the amplitude uniform from 0-80 linearly
		m_shader->setUniform("amplitude", elapsedTime * 16);
	}

	// faade out for the last 5 seconds
	if (elapsedTime > 15 && elapsedTime < 20) {
		// decrease the amplitude uniform from 80-0 linearly
		m_shader->setUniform("amplitude", (20 - (elapsedTime)) * 16);
	}

	// change the pitch of the music from 0.75 to 1.25 with a sin wave over time
	m_music->setPitch(1 + (sin(elapsedTime) * 0.25));

	// at 20 seconds disable the effect
	if (elapsedTime >= 20) {
		disable();
	}
}