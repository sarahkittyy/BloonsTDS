#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "Bloons/Loader.hpp"
#include "Bloons/Manager.hpp"
#include "Bloons/Path.hpp"
#include "Bloons/Wave.hpp"

namespace Bloons
{

/**
 * @brief Stores all map info.
 * This includes the paths, waves, and the bloon manager itself.
 * 
 */
class Map : public sf::Drawable
{
public:
	/**
	 * @brief Construct a new Map.
	 * 
	 * @param tileSize The size of a map tile.
	 */
	Map(unsigned tileSize = 1);

	/**
	 * @brief Propagates the given tilesize to the bloon manager,
	 * 
	 * @param tileSize The size of a map tile.
	 */
	void setTileSize(unsigned tileSize);

	/**
	 * @brief Add a path to the map.
	 * 
	 * @param path The path to add.
	 */
	void addPath(Path path);

	/**
	 * @brief Add a wave to the map.
	 * 
	 * @param wave The wave to add.
	 * 
	 * @remarks Note the order in which waves are appended, this will 
	 * be their ID (from 0) to call runWave() with.
	 */
	void addWave(Wave wave);

	/**
	 * @brief Run the wave with the given id.
	 * 
	 * @param id The index in which it was added with addWave(). 
	 */
	void runWave(size_t id);

	/**
	 * @brief Call once per frame.
	 * Updates bloon movements through the bloon manager.
	 * 
	 */
	void update();

	/**
	 * @brief Initialze the map from the given map config json file.
	 * 
	 * @param name The name of the config file.
	 */
	void init(std::string name);

private:
	/**
	 * @brief SFML's draw() override.
	 * 
	 * @remarks Just draws the bloonmanager.
	 * 
	 */
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	/**
	 * @brief The map paths.
	 * 
	 */
	std::vector<Path> mPaths;

	/**
	 * @brief The map waves.
	 * 
	 */
	std::vector<Wave> mWaves;

	/**
	 * @brief The map bloon manager.
	 * 
	 */
	Manager mBloonManager;
};

}