#pragma once

#include <fstream>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "Tilemap/Renderer.hpp"

#include "ResourceManager.hpp"

namespace Tilemap
{

/**
 * @brief Load the graphical tilemap data from Tiled.
 * 
 * @param resources The application resource manager.
 * @param renderer The tilemap renderer to load the data into.
 * @param path The path to the map json file.
 * 
 */
void loadGraphicsFromMap(ResourceManager& resources,
						 Renderer& renderer,
						 std::string path);

}