#pragma once

#include <SFML/Graphics.hpp>

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "Towers/Loader.hpp"
#include "Towers/Tower.hpp"

#include "ResourceManager.hpp"

#include "Economy.hpp"
#include "GUI/Towers.hpp"
#include "Tilemap/Renderer.hpp"

namespace Towers
{

/**
 * @brief Stores all placed down map towers and their information,
 * and serves as an API for getting/setting/placing towers.
 * 
 */
class Manager : public sf::Drawable
{
private:
	/**
	 * @brief The data structure for a held tower,
	 * including any extra data that needs to be carried with it.
	 * 
	 */
	struct HeldTower
	{
		/**
		 * @brief Construct a new Held Tower
		 * 
		 */
		HeldTower();

		/**
		 * @brief Construct a new Held Tower object
		 * 
		 * @param t new-allocated ptr to the tower.
		 * @param r The range of the tower.
		 */
		HeldTower(Tower* t, int r = -1);

		/**
		 * @brief Update the tower.
		 * 
		 * @param mouse_pos The mouse's current position.
		 * 
		 */
		void update(sf::Vector2f mouse_pos);

		/**
		 * @brief Set the state of the range circle,
		 * true means a normal circle, false means the circle
		 * turns red to indicate it's unplaceable.
		 * 
		 * @param placeable Whether or not the tower is placeable.
		 */
		void setRangeState(bool placeable);

		std::unique_ptr<Tower> tower;
		sf::CircleShape range;
	};

public:
	/**
	 * @brief Construct a new Manager object
	 * 
	 * @param resources The application resource manager.
	 * @param economy The application economy manager.
	 * @param renderer The application tilemap renderer.
	 * @param gui_towerloader The GUI tower loader.
	 */
	Manager(ResourceManager& resources,
			Economy& economy,
			Tilemap::Renderer* renderer,
			GUI::TowerLoader& gui_towerloader);

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
	 * @return true If the currently queued tower is placeable.
	 *  
	 */
	bool isQueuePlaceable();

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
	 * @brief Reference to the application economy.
	 * 
	 */
	Economy& mEconomy;

	/**
	 * @brief The application GUI tower loader.
	 * 
	 */
	GUI::TowerLoader& mGUITowerLoader;

	/**
	 * @brief Pointer to the main tilemap renderer.
	 * 
	 */
	Tilemap::Renderer* mMapRenderer;

	/**
	 * @brief Vector of all towers.
	 * 
	 */
	std::vector<Tower> mTowers;

	/**
	 * @brief The currently "queued" tower.
	 * 
	 */
	HeldTower mQueue;

	/**
	 * @brief Whether or not a tower is queued.
	 * 
	 */
	bool mQueued;
};

}