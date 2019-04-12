#pragma once

#include <SFML/Graphics.hpp>

#include <nlohmann/json.hpp>

#include <array>
#include <unordered_map>
#include <vector>

#include "ResourceManager.hpp"

/**
 * @brief A collection of Tilemap-related classes.
 * 
 */
namespace Tilemap
{

/**
 * @brief Renders a tilemap with the given settings.
 * 
 */
class Renderer : public sf::Drawable, public sf::Transformable
{
public:
	/**
	 * @brief Construct a new Renderer object
	 * 
	 */
	Renderer();

	/**
	 * @brief Configure the renderer.
	 * 
	 * @param settings The tilemap settings.
	 */
	void options(nlohmann::json settings);

	/**
	 * @brief Initialize the tilemap with the given settings.
	 * 
	 * @param resources The application resource manager.
	 */
	void init(ResourceManager& resources);

	/**
	 * @brief Get the boundaries of the map.
	 * 
	 * @return sf::FloatRect The map boundaries.
	 */
	sf::FloatRect getMapBounds();

	/**
	 * @brief Checks if the given boundary fits into the tilemap. 
	 * 
	 * @param bounds The boundaries to check.
	 *  
	 * @return true if it's a valid position in-bounds.
	 */
	bool isInBounds(sf::FloatRect bounds);

private:
	/**
	 * @brief SFML's draw() method 
	 *  
	 */
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	/**
	 * @brief The vertices of the map.
	 * 
	 */
	sf::VertexArray mVertices;

	/**
	 * @brief The map's texture.
	 * 
	 */
	sf::Texture* mTex;

	/**
	 * @brief The map's settings.
	 * 
	 */
	nlohmann::json mSettings;
};

}