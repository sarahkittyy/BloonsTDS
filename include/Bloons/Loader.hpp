#pragma once

#include <fstream>
#include <nlohmann/json.hpp>
#include <string>

#include "Bloons/Bloons.hpp"

namespace Bloons
{
namespace Loader
{

void loadMap(Map& map, std::string name);

}
}