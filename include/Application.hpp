#pragma once

#include <SFML/Graphics.hpp>

#include "imgui/imgui-SFML.h"
#include "imgui/imgui.h"

#include "Tilemap/Tilemap.hpp"
#include "Towers/Towers.hpp"

/**
 * @brief Main program starting point.
 * 
 */
class Application
{
public:
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
	 * @brief The tilemap renderer.
	 * 
	 */
	Tilemap::Renderer mMapRenderer;

	/**
	 * @brief The tower manager.
	 * 
	 */
	Towers::Manager mTowerManager;
};