#include "Bloons/Loader.hpp"

namespace Bloons
{

//Static Decl
std::unordered_map<std::string, Bloon> Loader::mBloons;
sf::Vector2u Loader::mTextureMapSize;
sf::Texture* Loader::mTexture;

void Loader::init(ResourceManager& resources)
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

	//Load the map size.
	mTextureMapSize = {
		bloon_data.at("mapsize")[0],
		bloon_data.at("mapsize")[1]};

	//Load the texture.
	mTexture = &resources.texture("resource/bloons/" + bloon_data.at("map").get<std::string>());

	for (auto& bloon : bloon_data.at("bloons").items())
	{
		//Create the variables to emplace into the map later.
		std::string name = bloon.key();
		Bloon bl;

		//Bloon data.
		json data = bloon.value();

		//Set the bloon speed.
		bl.setSpeed(data.at("speed").get<float>());

		//Set the bloon name.
		bl.setName(name);

		//Set the animation.
		bl.setAnimation({.frames = data.at("animation").at("frames").get<std::vector<unsigned>>(),
						 .speed  = data.at("animation")
									  .at("speed")
									  .get<float>()});

		//Iterate over all elements that the bloon pops to.
		for (auto& pop_to : data.at("pops-to").get<json::array_t>())
		{
			//Append the item to the Bloon instance.
			bl.addInside({.name = pop_to.at("bloon"),
						  .ct   = pop_to.at("count").get<unsigned>()});
		}

		//Emplace the final bloon template into the map.
		mBloons[name] = bl;
	}
}

Bloon& Loader::getBloon(std::string name)
{
	if (mBloons.find(name) == mBloons.end())
	{
		throw std::out_of_range("Bloon " + name + " not found.");
	}

	return mBloons[name];
}

sf::Texture* Loader::getBloonTexture()
{
	return mTexture;
}

sf::Vector2u Loader::getTextureMapSize()
{
	return mTextureMapSize;
}

}