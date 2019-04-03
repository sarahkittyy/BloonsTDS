#pragma once

#include <SFML/Graphics.hpp>

#include <cstdlib>
#include <ctime>

#include "imgui/imgui-SFML.h"
#include "imgui/imgui.h"

#include "ResourceManager.hpp"

#include "Bloons/Bloons.hpp"
#include "Bloons/Map.hpp"
#include "Tilemap/Tilemap.hpp"
#include "Towers/Towers.hpp"

/**d
 * @brief Main program starting point.
 * 
 */
class Application
{
public:
	/**
	 * @brief Construct a new Application.
	 * 
	 */
	Application();

	/**
	 * @brief The entry point of the program.
	 * 
	 * @return int Exit code.
	 */
	int run();

private:
	/**
	 * @brief SFML's window.
	 * 
	 */
	sf::RenderWindow mWindow;

	/**
	 * @brief The size of the window.
	 * 
	 */
	static sf::Vector2u WINDOW_SIZE;

	/**
	 * @brief The main application resource manager.
	 * 
	 */
	ResourceManager mResources;

	/**
	 * @brief The tilemap renderer.
	 * 
	 */
	Tilemap::Renderer mMapRenderer;

	/**
	 * @brief The tower manager.
	 * 
	 */
	Towers::Manager mTowerManager;

	/**
	 * @brief The bloon map.
	 * 
	 */
	Bloons::Map mMap;
};