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