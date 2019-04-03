#include "Bloons/Map.hpp"

namespace Bloons
{

Map::Map()
	: mBloonManager(mPaths)
{
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mBloonManager, states);
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
	mBloonManager.runWave(mWaves[id]);
}

void Map::update()
{
	mBloonManager.update();
}

void Map::init(std::string name)
{
	using nlohmann::json;

	//Get the map data.
	std::ifstream file("resource/maps/data/" + name + ".json");
	json map_data;
	file >> map_data;
	file.close();

	//Usually the size of the tile,
	//multiplies the path position
	//by this value. Used for convenience
	float factor = map_data.at("path-factor").get<float>();

	//Iterate over all paths of the map.
	for (auto& path : map_data.at("paths")
						  .get<std::vector<json::array_t>>())
	{
		Path cpath;

		//Iterate over all positions of the path.
		for (auto& pos_arr : path)
		{
			sf::Vector2f pos{
				pos_arr[0].get<float>() * factor, pos_arr[1].get<float>() * factor};

			//Append the position to the path.
			cpath.addNode({.pos = pos});
		}

		//Append the path.
		addPath(cpath);
	}

	//Iterate over all waves.
	for (auto& wave : map_data.at("waves"))
	{
		Wave cwave;

		//Iterate over all groups.
		for (auto& group : wave.at("groups"))
		{
			//Load the bloon
			Bloon b = Loader::getBloon(group.at("bloon").get<std::string>());
			//Get the spacing.
			float spacing = group.at("spacing").get<float>();
			//Get the bloon count.
			unsigned count = group.at("count").get<unsigned>();
			//Get the duration.
			float dur = group.at("dur").get<float>();

			//Add the group.
			// clang-format off
			cwave.addGroup({
				.bloon = b,
				.spacing = (time_t)(spacing*60.f),
				.ct = (size_t)count,
				.dur = (time_t)(dur*60.f)
			});
			// clang-format on
		}

		//Append the wave.
		addWave(cwave);
	}

	mBloonManager = Manager(mPaths);
}

}