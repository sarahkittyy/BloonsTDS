#include "Bloons/Bloon.hpp"

namespace Bloons
{

void Bloon::setSpeed(float newSpeed)
{
	mSpeed = newSpeed;
}

float Bloon::getSpeed()
{
	return mSpeed;
}

void Bloon::setName(std::string newName)
{
	mName = newName;
}

std::string Bloon::getName()
{
	return mName;
}

void Bloon::setAnimation(AnimatedSprite::Animation animation)
{
	mAnimation = animation;
}

const AnimatedSprite::Animation& Bloon::getAnimation()
{
	return mAnimation;
}

void Bloon::addInside(Inside in)
{
	mInsides.push_back(in);
}

void Bloon::clearInsides()
{
	mInsides.clear();
}

const std::vector<Bloon::Inside>& Bloon::getInsides()
{
	return mInsides;
}

}