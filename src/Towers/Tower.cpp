#include "Towers/Tower.hpp"

namespace Towers
{

Tower::Tower(sf::Texture* tex)
	: mTex(tex),
	  mSprite(mTex)   //<-- Initialize the sprite & texture
{
}


Tower::~Tower()
{
}

void Tower::update()
{
	//Update the internal animated sprite.
	mSprite.update();
}

void Tower::setName(std::string name)
{
	mName = name;
}

std::string Tower::getName() const
{
	return mName;
}

void Tower::setTexture(sf::Texture* tex)
{
	mTex = tex;
	mSprite.setTexture(mTex);
}

void Tower::addUpgrade(std::string name, AnimatedSprite::Animation anim)
{
	mSprite.addAnimation(name, anim);
}

void Tower::setUpgrade(std::string name)
{
	mSprite.setAnimation(name);
}

void Tower::setTextureMapSize(sf::Vector2u size)
{
	mSprite.setTextureMapSize(size);
}

sf::FloatRect Tower::getGlobalBounds()
{
	return getTransform().transformRect(mSprite.getGlobalBounds());
}

void Tower::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mSprite, states);
}

}