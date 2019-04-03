#include "Bloons/Renderer.hpp"

namespace Bloons
{

Renderer::Renderer(std::string bloon)
	: mSpr(Loader::getBloonTexture()),
	  mBloon(Loader::getBloon(bloon))
{
	//Init the animated sprite.
	updateSprite();
}

void Renderer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mSpr, states);
}

void Renderer::update()
{
	//Update the animated sprite.
	mSpr.update();
}

void Renderer::updateSprite()
{
	//Init the animted sprite...
	mSpr = AnimatedSprite(Loader::getBloonTexture());
	mSpr.addAnimation("default", mBloon.getAnimation());
	mSpr.setAnimation("default");
	mSpr.setTextureMapSize(Loader::getTextureMapSize());
}

}