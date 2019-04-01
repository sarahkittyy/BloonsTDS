#include "Towers/Tower.hpp"

namespace Towers
{

Tower::Tower(sf::Texture& tex)
	: mTex(tex),
	  mSprite(mTex)
{
}

Tower::~Tower()
{
}

void Tower::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mSprite, states);
}

}