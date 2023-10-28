#pragma once
#include <SFML/Graphics.hpp>

class TextureHandler {
private:
public:
	// static load texture methods
	// 
	// loads a texture onto a sprite with a size
	static bool loadTexture(sf::Texture& tex, sf::Sprite& sprite, std::string sFilename, sf::Vector2f& size);
	// loads a texture with multiple frames
	static bool loadTexture(sf::Texture& tex, sf::Sprite& sprite, std::string sFilename, sf::Vector2f& size, int frameWidth, int frameHeight, int frameCount);
	// just loads a texture from a file into a sf::Texture, used to store power up textures
	static bool loadTexture(sf::Texture& tex, std::string sFilename);
};