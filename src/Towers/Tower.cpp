#include "Towers/Tower.hpp"

namespace Towers
{

Tower::Tower(sf::Texture* tex)
	: mTex(tex),
	  mSprite(mTex)   //<-- Initialize the sprite & texture
{
	mCurrentUpgrade = 0;
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

void Tower::addUpgrade(Upgrade upgrade)
{
	mSprite.addAnimation(upgrade.name, upgrade.anim);
}

void Tower::setUpgrade(std::string name)
{
	mSprite.setAnimation(name);
	//Find the current upgrade and set mCurrentUpgrade to it.
	for (unsigned i = 0; i < mUpgrades.size(); ++i)
	{
		if (mUpgrades[i].name == name)
		{
			mCurrentUpgrade = i;
			break;
		}
	}
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