#include "Bloons/Loader.hpp"

namespace Bloons
{
namespace Loader
{

std::unordered_map<std::string, Bloon> BloonLoader::mBloons;

void BloonLoader::init()
{
	using nlohmann::json;

	//Load bloon config data.
	std::ifstream file("resource/bloons/bloons.json");
	if (!file)
	{
		throw std::runtime_error("Could not open bloon config file!");
	}
	json bloon_data;
	file >> bloon_data;
	file.close();

	for (auto& bloon : bloon_data.at("bloons").items())
	{
		//Create the variables to emplace into the map later.
		std::string name = bloon.key();
		Bloon bl;

		//Bloon data.
		json data = bloon.value();

		//Set the bloon speed.
		bl.setSpeed(data.at("speed").get<float>());

		//Iterate over all elements that the bloon pops to.
		for (auto& pop_to : data.at("pops-to").get<json::array_t>())
		{
			//Append the item to the Bloon instance.
			bl.addInside({
				.name = pop_to.at("name"),
				.ct = pop_to.at("count").get<unsigned>()
			});
		}

		//Emplace the final bloon template into the map.
		mBloons[name] = bl;
	}
}

const Bloon& BloonLoader::getBloon(std::string name)
{
	if(mBloons.find(name) == mBloons.end())
	{
		throw std::out_of_range("Bloon " + name + " not found.");
	}
	
	return mBloons[name];
}

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
			Bloon b = BloonLoader::getBloon(group.at("bloon").get<std::string>());
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