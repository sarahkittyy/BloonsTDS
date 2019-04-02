#pragma once

#include <SFML/Graphics.hpp>

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
	 * @brief Updates all internal towers.
	 * 
	 */
	void update();

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
};

}