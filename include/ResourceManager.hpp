#pragma once

#include <SFML/Graphics.hpp>

#include <string>
#include <unordered_map>

/**
 * @brief Manages textures so that only one of every texture is ever
 * instanced at a time.
 * 
 */
class ResourceManager
{
public:
	/**
	 * @brief Retrieve the texture at the given path.
	 * 
	 * @param path The path of the texture.
	 * @return sf::Texture& A ref to the texture.
	 */
	sf::Texture& texture(std::string path);

private:
	/**
	 * @brief The internal map of textures.
	 * 
	 */
	std::unordered_map<std::string, sf::Texture> mTextures;
};