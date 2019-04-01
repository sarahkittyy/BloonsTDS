#pragma once

#include <SFML/Graphics.hpp>

#include "AnimatedSprite.hpp"

namespace Towers
{

class Tower : public sf::Drawable, public sf::Transformable
{
public:
	Tower(sf::Texture* tex);

	virtual ~Tower();

	void update();

	void setTexture(sf::Texture* tex);

	void addUpgrade(std::string name, AnimatedSprite::Animation anim);

	void setUpgrade(std::string name);

	void setTextureMapSize(sf::Vector2u size);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Texture* mTex;
	AnimatedSprite mSprite;
};

}