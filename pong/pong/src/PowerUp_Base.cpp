#include "PowerUp_Base.h"

// set the texture from the filename using the texture handler class
void PowerUp_Base::setTexture(std::string sFilename) {
	TextureHandler::loadTexture(m_Texture, sFilename);
}

// retrieve the texture
sf::Texture PowerUp_Base::getTexture() {
	return m_Texture;
}

// set the m_activated flag
void PowerUp_Base::setActive(bool active) {
	m_activated = active;
}

// get the m_activated flag
bool PowerUp_Base::getActive() {
	return m_activated;
}