#pragma once

#include <fstream>
#include <nlohmann/json.hpp>
#include <string>

#include "Bloons/Bloon.hpp"
#include "ResourceManager.hpp"

namespace Bloons
{
/**
 * @brief Mostly static class to load bare copyable instances
 * of bloons and their properties.
 * 
 */
class Loader
{
public:
	/**
	 * @brief Call this ONCE.
	 * Initializes bloons from the default config file.
	 * 
	 * @param resources Reference to the application resource manager.
	 */
	static void init(ResourceManager& resources);

	/**
	 * @brief Get the bloon with the given name.
	 * 
	 * @param name The name of the bloon.
	 * @return Bloon& A reference to the bloon.
	 */
	static Bloon& getBloon(std::string name);

	/**
	 * @brief Get the bloon texture.
	 * 
	 * @return sf::Texture* The bloon texture.
	 */
	static sf::Texture* getBloonTexture();

	/**
	 * @brief Get the Texture Map Size.
	 * 
	 * @return sf::Vector2u The texture map size.
	 */
	static sf::Vector2u getTextureMapSize();

private:
	/**
	 * @brief A map of names to their bloons.
	 * 
	 * @remarks The names are also stored in the bloon, but it's
	 * more convenient to map them by a copy of their name also.
	 * 
	 */
	static std::unordered_map<std::string, Bloon> mBloons;

	/**
	 * @brief The size of the texture map grid, for the animated sprite.
	 * 
	 */
	static sf::Vector2u mTextureMapSize;

	/**
	 * @brief Ptr to the texture map for all bloons.
	 * 
	 */
	static sf::Texture* mTexture;
};

}