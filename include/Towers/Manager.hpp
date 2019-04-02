#pragma once

#include <SFML/Graphics.hpp>

#include <string>
#include <unordered_map>
#include <vector>

#include "Towers/Loader.hpp"
#include "Towers/Tower.hpp"

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
	 * @brief The resource map, so that we can use the same texture
	 * for multiple towers.
	 * 
	 * @remarks Textures from here are passed to newly initialized towers.
	 * 
	 */
	std::unordered_map<std::string, sf::Texture> mResources;

	/**
	 * @brief Gets the texture from the specified tower name/key,
	 * creating one if it does not exist.
	 * 
	 * @param key The texture's name/key.
	 * @return sf::Texture& A reference to the texture at that key.
	 */
	sf::Texture& getTexture(std::string key);

	/**
	 * @brief Vector of all towers.
	 * 
	 */
	std::vector<Tower> mTowers;
};

}