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
	struct TowerFramework
	{
		std::string name;
		sf::Vector2f pos;
	};

	Manager();

	void placeTower(TowerFramework framework);

	void update();

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	std::unordered_map<std::string, sf::Texture> mResources;

	sf::Texture& getTexture(std::string key);

	std::vector<Tower> mTowers;
};

}