#include "Bloons/Renderer.hpp"

namespace Bloons
{

Renderer::Renderer(std::string bloon)
	: mSpr(Loader::BloonLoader::getBloonTexture()),
	  mBloon(Loader::BloonLoader::getBloon(bloon))
{
	updateSprite();
}

void Renderer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mSpr, states);
}

void Renderer::update()
{
	mSpr.update();
}

void Renderer::updateSprite()
{
	mSpr = AnimatedSprite(Loader::BloonLoader::getBloonTexture());
	mSpr.addAnimation("default", mBloon.getAnimation());
	mSpr.setAnimation("default");
	mSpr.setTextureMapSize(Loader::BloonLoader::getTextureMapSize());
}

}