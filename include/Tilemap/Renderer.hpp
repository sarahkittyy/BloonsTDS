#pragma once

#include <SFML/Graphics.hpp>

#include <nlohmann/json.hpp>

#include <array>
#include <unordered_map>
#include <vector>

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
	 */
	void init();

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
	sf::Texture mTex;

	/**
	 * @brief The map's settings.
	 * 
	 */
	nlohmann::json mSettings;
};

}