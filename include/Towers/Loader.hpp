#pragma once

#include <SFML/Graphics.hpp>
#include <fstream>
#include <nlohmann/json.hpp>
#include <vector>

#include "AnimatedSprite.hpp"
#include "Towers/Tower.hpp"

namespace Towers
{

/**
 * @brief Loads the tower from the given name.
 * 
 * @param tower The tower to configure.
 * @param tex The texture to configure & use.
 * @param name The name of the tower to load.
 */
void loadTowerFromName(Tower& tower, sf::Texture* tex, std::string name);

}