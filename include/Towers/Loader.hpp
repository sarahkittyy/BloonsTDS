#pragma once

#include <SFML/Graphics.hpp>
#include <fstream>
#include <nlohmann/json.hpp>
#include <vector>

#include "AnimatedSprite.hpp"
#include "Towers/Tower.hpp"

namespace Towers
{

void loadTowerFromName(Tower& tower, sf::Texture* tex, std::string name);

}