#pragma once

#include <SFML/Graphics.hpp>

#include <cmath>
#include <functional>

#include "Bloons/Bloon.hpp"
#include "Bloons/Path.hpp"
#include "Bloons/Renderer.hpp"
#include "Bloons/Wave.hpp"

namespace Bloons
{

/**
 * @brief An API for handling bloon logic, storing bloons with their positions,
 * and moving them along the path.
 * 
 */
class Manager : public sf::Drawable
{
private:
	/**
	 * @brief A data type that stores a bloon renderer,
	 * a copy of path it is traversing,
	 * a copy of the bloon it is rendering,
	 * and whether or not that bloon is alive.
	 * 
	 */
	struct BloonSprite
	{
		Renderer r;
		Path path;
		Bloon bloon;
		bool alive;
	};

public:
	/**
	 * @brief Construct a new Manager.
	 * 
	 * @param paths All possible map paths.
	 */
	Manager(std::vector<Path>& paths);

	/**
	 * @brief Run a given wave.
	 * 
	 * @param w The wave to run.
	 */
	void runWave(Wave w);

	/**
	 * @brief Update the manager. Call once per frame.
	 * 
	 */
	void update();

private:
	/**
	 * @brief SFML's draw() override.
	 * 
	 */
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	/**
	 * @brief Callback from mCurrentWave, sends a bloon.
	 * 
	 * @param b The bloon to send.
	 */
	void sendBloon(Bloon& b);

	/**
	 * @brief The currently running wave.
	 * 
	 */
	Wave mCurrentWave;

	/**
	 * @brief All the possible paths for the bloons of this wave.
	 * 
	 */
	std::vector<Path> mPaths;

	/**
	 * @brief The index of the path we are currently sending bloons down.
	 * Changes each send to send bloons through all paths equally.
	 * 
	 */
	size_t mPathIndex;

	/**
	 * @brief Move the path index forward.
	 * 
	 */
	void nextPath();

	/**
	 * @brief Get the current path we are sending the bloon down.
	 * 
	 * @return Path The path to send the bloon down.
	 * 
	 * @see nextPath().
	 */
	Path getPath();

	/**
	 * @brief All the visible, rendered bloons.
	 * 
	 */
	std::vector<BloonSprite> mBloons;

	/**
	 * @brief Get the x/y distance between two points.
	 * 
	 * @param now Point A
	 * @param next Point B
	 * @return sf::Vector2f next - now.
	 */
	sf::Vector2f dist(sf::Vector2f now, sf::Vector2f next);
};

}