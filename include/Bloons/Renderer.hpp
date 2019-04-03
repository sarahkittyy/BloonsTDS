#pragma once

#include <SFML/Graphics.hpp>

#include "AnimatedSprite.hpp"
#include "Bloons/Bloon.hpp"
#include "Bloons/Loader.hpp"
#include "ResourceManager.hpp"

namespace Bloons
{

/**
 * @brief Renders a bloon passed to it.
 * 
 */
class Renderer : public sf::Drawable, public sf::Transformable
{
public:
	/**
	 * @brief Construct a new Renderer.
	 * 
	 * @param bloon The name of the bloon to render.
	 */
	Renderer(std::string bloon);

	/**
	 * @brief Updates the internal animated sprite.
	 * 
	 * @remarks Call once per frame.
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
	 * @brief The sprite to render.
	 * 
	 */
	AnimatedSprite mSpr;

	/**
	 * @brief The bloon to render.
	 * 
	 */
	Bloon mBloon;

	/**
	 * @brief Updates the sprite with the bloon settings.
	 * 
	 */
	void updateSprite();
};

}