#pragma once

#include <imgui/imgui.h>
#include <SFML/Graphics.hpp>

#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

#include "ResourceManager.hpp"

namespace GUI
{

/**
 * @brief A Tower GUI element, containing information
 * on texture, name, & description, and any other info.
 * 
 */
class Tower
{
public:
	/**
	 * @brief Construct a new Tower.
	 * 
	 * @param r The application resource manager.
	 * @param name The name of the tower to load.
	 * @param size The size of the tower once loaded.
	 */
	Tower(ResourceManager* r,
		  std::string name,
		  sf::Vector2f size);

	/**
	 * @brief Get the Sprite.
	 * 
	 * @return sf::Sprite The sprite of the tower.
	 */
	sf::Sprite getSprite();

	/**
	 * @brief Get the tower's name.
	 * 
	 */
	std::string getName();

	/**
	 * @brief Get the actual name of the tower (name of the .json file)
	 * 
	 */
	std::string getActualName();

	/**
	 * @brief Get the tower's description.
	 * 
	 */
	std::string getDesc();

	/**
	 * @brief Get the tower's cost.
	 * 
	 */
	int getCost();

	/**
	 * @brief Get the tower's range.
	 *  
	 */
	int getRange();

	/**
	 * @brief Get the tower's hotkey.
	 * 
	 * @return sf::Keyboard::Key The tower's shortcut hotkey.
	 */
	sf::Keyboard::Key getHotkey();

private:
	/**
	 * @brief The tower's name.
	 * 
	 */
	std::string name;

	/**
	 * @brief The tower's actual name.
	 * 
	 */
	std::string actualName;

	/**
	 * @brief The tower's description.
	 * 
	 */
	std::string desc;

	/**
	 * @brief The cost of the tower.
	 * 
	 */
	int cost;

	/**
	 * @brief The tower's range.
	 * 
	 */
	int range;

	/**
	 * @brief The hotkey to press the tower.
	 * 
	 */
	sf::Keyboard::Key hotkey;

	/**
	 * @brief The tower's texture.
	 * 
	 */
	sf::Texture* tex;

	/**
	 * @brief The sprite, initialized from the tower's texture.
	 * 
	 */
	sf::Sprite spr;

	/**
	 * @brief Loads the sprite.
	 * 
	 * @param tower The tower's json information.
	 * @param size The size of the tower, once loaded.
	 */
	void loadSprite(nlohmann::json tower, sf::Vector2f size);

	/**
	 * @brief The pointer to the application resource manager.
	 * 
	 */
	ResourceManager* mResources;
};

/**
 * @brief Loads the towers, storing them so that they don't have
 * to be re-read every call.
 * 
 */
class TowerLoader
{
public:
	/**
	 * @brief Construct a new Tower Loader.
	 * 
	 * @param r The application resource manager. 
	 * @param size The size of each tower sprite to load.
	 * 
	 * @remarks A size of -1, -1 indicates use the default size in the texture itself.
	 */
	TowerLoader(ResourceManager* r, sf::Vector2f size = {-1, -1});

	/**
	 * @brief Get a vector of all available game towers.
	 * 
	 * @param r Pointer the the application's resource manager.
	 * 
	 * @return std::vector<Tower> A vector of all in-game tower options.
	 */
	std::vector<Tower>& getGuiTowers();

	/**
	 * @brief Get a GUI tower by it's name.
	 * 
	 * @param name The name of the tower.
	 * @return Tower& The retrieved tower.
	 */
	Tower& getGuiTowerByName(std::string name);

private:
	/**
	 * @brief The loaded towers.
	 * Loaded through the constructor.
	 * 
	 */
	std::vector<Tower> mTowers;

	/**
	 * @brief The pointer to the application resource manager.
	 * 
	 */
	ResourceManager* mResources;
};

}