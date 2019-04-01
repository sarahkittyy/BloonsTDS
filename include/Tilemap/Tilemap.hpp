#pragma once

#include <fstream>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "Tilemap/Renderer.hpp"

namespace Tilemap
{

/**
 * @brief Load the graphical tilemap data from Tiled.
 * 
 * @param renderer The tilemap renderer to load the data into.
 * @param path The path to the map json file.
 * 
 */
void loadGraphicsFromMap(Renderer& renderer, std::string path);

}