#pragma once

#include <SFML/Graphics.hpp>

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "Towers/Loader.hpp"
#include "Towers/Tower.hpp"

#include "ResourceManager.hpp"

namespace Towers
{

/**
 * @brief Stores all placed down map towers and their information,
 * and serves as an API for getting/setting/placing towers.
 * 
 */
class Manager : public sf::Drawable
{
public:
	/**
	 * @brief Construct a new Manager object
	 * 
	 * @param resources The application resource manager.
	 */
	Manager(ResourceManager& resources);

	/**
	 * @brief Data structure for placing new towers.
	 * 
	 * @param name The name of the tower (equal to the name of the .json file for configuring the tower.)
	 * 
	 * @param pos The position of the tower.
	 * 
	 */
	struct TowerFramework
	{
		std::string name;
		sf::Vector2f pos;
	};

	/**
	 * @brief Place a tower with the given TowerFramework settings.
	 * 
	 * @param framework The data of the tower to place.
	 */
	void placeTower(TowerFramework framework);

	/**
	 * @brief Places down the queued tower.
	 * 
	 */
	void placeQueuedTower();

	/**
	 * @brief Updates all internal towers.
	 * 
	 */
	void update();

	/**
	 * @brief Place a tower in the player's "hand" -- doesn't
	 * update it, but is used as a visual for placing towers.
	 * 
	 * @param name The name of the tower.
	 */
	void queueTower(std::string name);

	/**
	 * @brief Unqueue the currently queue'd tower.
	 * 
	 */
	void unqueueTower();

	/**
	 * @return true If a tower is queued.
	 *   
	 */
	bool isQueued();

	/**
	 * @brief Get the bounds of the queue'd tower.
	 * 
	 * @return sf::FloatRect The bounds of the queue'd tower.
	 */
	sf::FloatRect getQueuedTowerBounds();

	/**
	 * @brief Return a const reference to the queue'd tower.
	 * 
	 * @return const Tower& The queue'd tower.
	 */
	const Tower& queuedTower();

private:
	/**
	 * @brief SFML's draw() override. Draws all towers.
	 * 
	 */
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	/**
	 * @brief The application resource manager.
	 * 
	 */
	ResourceManager& mResources;

	/**
	 * @brief Vector of all towers.
	 * 
	 */
	std::vector<Tower> mTowers;

	/**
	 * @brief The currently "queued" tower.
	 * 
	 */
	std::unique_ptr<Tower> mQueue;

	/**
	 * @brief Whether or not a tower is queued.
	 * 
	 */
	bool mQueued;
};

}