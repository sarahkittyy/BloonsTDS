#include "Bloons/Loader.hpp"

namespace Bloons
{
namespace Loader
{

void loadMap(Map& map, std::string name)
{
	using nlohmann::json;

	//Get the map data.
	std::ifstream file("resource/maps/data/" + name + ".json");
	json map_data;
	file >> map_data;
	file.close();

	//Iterate over all paths of the map.
	for (auto& path : map_data.at("paths")
						  .get<std::vector<json::array_t>>())
	{
		Path cpath;

		//Iterate over all positions of the path.
		for (auto& pos_arr : path)
		{
			sf::Vector2f pos{
				pos_arr[0], pos_arr[1]};

			//Append the position to the path.
			cpath.addNode({.pos = pos});
		}

		//Append the path.
		map.addPath(cpath);
	}

	//Iterate over all waves.
	for (auto& wave : map_data.at("waves"))
	{
		Wave cwave;

		//Iterate over all groups.
		for (auto& group : wave.at("groups"))
		{
			//Load the bloon
			Bloon b;   //TODO: LOAD BLOON
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
				.spacing = (time_t)spacing*60,
				.ct = (time_t)count,
				.dur = (time_t)dur*60
			});
			// clang-format on
		}

		//Append the wave.
		map.addWave(cwave);
	}
}

}
}