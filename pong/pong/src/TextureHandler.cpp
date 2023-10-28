#include "TextureHandler.h"

// loads a texture onto a sprite with a size
bool TextureHandler::loadTexture(sf::Texture& tex, sf::Sprite& sprite, std::string sFilename, sf::Vector2f& size) {
	bool bSuccess;
	// loads the texture from file and returns false if failed
	bSuccess = tex.loadFromFile(".\\assets\\textures\\" + sFilename);
	if (!bSuccess) return false;

	// sets the scale, origin and texture of the sprite
	sprite.setScale(size.x / tex.getSize().x, size.y / tex.getSize().y);
	sprite.setOrigin(size.x / 2.0f / sprite.getScale().x, size.y / 2.0f / sprite.getScale().y);
	sprite.setTexture(tex);

	return true;
}

// loads a texture with multiple frames
bool TextureHandler::loadTexture(sf::Texture& tex, sf::Sprite& sprite, std::string sFilename, sf::Vector2f& size, int frameWidth, int frameHeight, int frameCount) {
	bool bSuccess;
	// loads the texture from file and returns false if failed
	bSuccess = tex.loadFromFile(".\\assets\\textures\\" + sFilename);
	if (!bSuccess) return false;

	// sets the scale and origin of the sprite
	sprite.setScale(size.x / tex.getSize().x, size.y / tex.getSize().y * frameCount);
	sprite.setOrigin(size.x / 2.0f / sprite.getScale().x, size.y / 2.0f / sprite.getScale().y);

	// sets the texture and current texture rectangle
	sprite.setTexture(tex);
	sprite.setTextureRect(sf::IntRect(0, 0, frameWidth, frameHeight));
	return true;
}

// just loads a texture from a file into a sf::Texture, used to store power up textures
bool TextureHandler::loadTexture(sf::Texture& tex, std::string sFilename) {
	bool bSuccess;
	// loads the texture from file and returns true if successful
	bSuccess = tex.loadFromFile(".\\assets\\textures\\" + sFilename);
	if (!bSuccess) return false;

	return true;
}