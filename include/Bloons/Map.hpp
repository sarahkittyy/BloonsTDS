#pragma once

#include <string>
#include <vector>

#include "Bloons/Path.hpp"
#include "Bloons/Wave.hpp"

namespace Bloons
{

class Map
{
public:
	Map();

	void addPath(Path path);

	void addWave(Wave wave);

	void runWave(size_t id);

	void update();

private:
	std::vector<Path> mPaths;
	std::vector<Wave> mWaves;
};

}