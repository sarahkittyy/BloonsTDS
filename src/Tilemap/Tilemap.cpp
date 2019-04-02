#include "Tilemap/Tilemap.hpp"

void Tilemap::loadGraphicsFromMap(Tilemap::Renderer& renderer,
								  std::string path)
{
	using nlohmann::json;
	std::ifstream file(path);
	if (!file)
	{
		throw std::runtime_error(path + " json file not found.");
	}

	//Read the json file.
	json data;
	file >> data;
	file.close();

	//Set the options.
	// clang-format off
	renderer.options({
		{"grid_size", 
			{
				data["width"].get<int>(),
				data["height"].get<int>()
			}
		},
		{"texture_path", 
			"resource/maps/" + data["tilesets"][0]["image"]
							.get<std::string>()
		},
		{"tiles", data["layers"][0]["data"].get<std::vector<int>>()},
		{"in_tile_size", 
			{
				data["tilewidth"].get<int>(),
				data["tileheight"].get<int>()
			}
		},
		{"out_tile_size",
			{
				data["tilewidth"].get<int>(),
				data["tileheight"].get<int>()
			}
		}
	});
	// clang-format on

	renderer.init();
}