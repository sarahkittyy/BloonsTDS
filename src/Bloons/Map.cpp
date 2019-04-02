#include "Bloons/Map.hpp"

namespace Bloons
{

Map::Map()
{
}

void Map::addPath(Path path)
{
	mPaths.push_back(path);
}

void Map::addWave(Wave wave)
{
	//wave.setBloonCallback(..);
	mWaves.push_back(wave);
}

void Map::runWave(size_t id)
{
}

void Map::update()
{
}

}