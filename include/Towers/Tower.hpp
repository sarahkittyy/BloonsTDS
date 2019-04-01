#pragma once

#include <SFML/Graphics.hpp>

#include "AnimatedSprite.hpp"

namespace Towers
{

class Tower : public sf::Drawable, public sf::Transformable
{
public:
	Tower(sf::Texture& tex);

	virtual ~Tower();

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Texture& mTex;
	AnimatedSprite mSprite;
};

}