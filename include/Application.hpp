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

#include "GUI/Towers.hpp"

#include "Economy.hpp"
#include "Util.hpp"

/**
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
	 * @brief Renders ImGui components.
	 * 
	 */
	void renderGui();

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
	 * @brief The main economy object of the game.
	 * 
	 */
	Economy mEconomy;

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

	/**
	 * @brief GUI Tower loader.
	 * 
	 */
	GUI::TowerLoader mGUITowerLoader;
};