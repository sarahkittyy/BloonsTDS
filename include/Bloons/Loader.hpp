#pragma once

#include <fstream>
#include <nlohmann/json.hpp>
#include <string>

#include "Bloons/Bloons.hpp"
#include "Bloons/Map.hpp"

namespace Bloons
{
namespace Loader
{

/**
 * @brief Initialze the given map from the given map config json file.
 * 
 * @param map The map to initialize.
 * @param name The name of the config file.
 */
void loadMap(Map& map, std::string name);

/**
 * @brief Mostly static class to load bare copyable instances
 * of bloons and their properties.
 * 
 */
class BloonLoader
{
public:
	/**
	 * @brief Call this ONCE.
	 * Initializes bloons from the default config file.
	 * 
	 */
	static void init();

	/**
	 * @brief Get the bloon with the given name.
	 * 
	 * @param name The name of the bloon.
	 * @return const Bloon& A const reference to the bloon.
	 */
	static const Bloon& getBloon(std::string name);

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
};

}
}