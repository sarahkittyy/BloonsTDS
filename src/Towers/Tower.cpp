#include "Towers/Tower.hpp"

namespace Towers
{

Tower::Tower(sf::Texture* tex)
	: mTex(tex),
	  mSprite(mTex)
{
}


Tower::~Tower()
{
}

void Tower::update()
{
	mSprite.update();
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

void Tower::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mSprite, states);
}

}