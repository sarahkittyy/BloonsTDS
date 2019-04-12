#include "Towers/Loader.hpp"

void Towers::loadTowerFromName(Tower& tower, sf::Texture* tex, std::string name)
{
	using nlohmann::json;

	json data;

	//Read the json from the file.
	std::ifstream file;
	file.open("resource/towers/" + name + ".json");
	file >> data;
	file.close();

	// clang-format off
	json defaults = {
		{"sprite", "dart-monkey.png"},
		{"mapsize", {1, 1}},
		{"animations", {
				{"default", {
					{"speed", -1},
					{"frames", {0}}	
				}}
		}},
		{"animation_start", "default"}	
	};
	// clang-format on

	auto valAt = [&](std::string key) -> json& {
		auto found = data.find(key);
		if (found == data.end())
		{
			return defaults[key];
		}
		else
		{
			return data[key];
		}
	};

	//Initialize the tower.
	tower.setName(name);
	if (tex->getSize().x + tex->getSize().y == 0)
	{
		tex->loadFromFile("resource/towers/" +
						  valAt("sprite")
							  .get<std::string>());
	}
	tower.setTexture(tex);
	for (auto& item : valAt("animations").items())
	{
		// clang-format off
		tower.addUpgrade(item.key(), {
			.frames = item.value().at("frames").get<std::vector<unsigned>>(),
			.speed = item.value().at("speed").get<float>()
		});
		// clang-format on
	}

	tower.setUpgrade(valAt("animation_start").get<std::string>());
	auto mapsize = valAt("mapsize").get<std::vector<unsigned>>();
	tower.setTextureMapSize({mapsize[0],
							 mapsize[1]});
}