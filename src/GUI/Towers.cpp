#include "GUI/Towers.hpp"

namespace GUI
{

Tower::Tower(ResourceManager* r,
			 std::string name,
			 sf::Vector2f size)
	: mResources(r)
{
	using nlohmann::json;

	//Load the tower's info to json
	std::ifstream file("resource/towers/" + name + ".json");
	json tower;
	file >> tower;
	file.close();
	//

	//Get the tower info
	json info  = tower["info"];
	this->name = info["name"];
	desc	   = info["desc"];
	cost	   = info["cost"].get<int>();
	range	  = info["range"].get<int>();

	actualName = name;

	//load the texture/sprite.
	loadSprite(tower, size);
}

void Tower::loadSprite(nlohmann::json tower, sf::Vector2f size)
{
	using nlohmann::json;

	//Path to the texture.
	std::string path = "resource/towers/" + tower["sprite"].get<std::string>();

	//Load the texture.
	tex = &mResources->texture(path);

	//Initialize the sprite.
	spr.setTexture(*tex, true);

	//We will use the first frame of the sprite map as the icon
	sf::IntRect bounds{
		0, 0,
		(int)tex->getSize().x / tower["mapsize"][0].get<int>(),
		(int)tex->getSize().y / tower["mapsize"][1].get<int>()};
	spr.setTextureRect(bounds);

	//If the size is valid
	if (size.x != -1 && size.y != -1)
	{
		//Set the sprite scaling.
		spr.setScale(size.x / spr.getGlobalBounds().width,
					 size.y / spr.getGlobalBounds().height);
	}
}

sf::Sprite Tower::getSprite()
{
	return spr;
}

std::string Tower::getName()
{
	return name;
}

std::string Tower::getActualName()
{
	return actualName;
}

std::string Tower::getDesc()
{
	return desc;
}

int Tower::getCost()
{
	return cost;
}

int Tower::getRange()
{
	return range;
}

////////////////////////////////////////////
//                                        //
// 				TOWER LOADER              //
//										  //
////////////////////////////////////////////

TowerLoader::TowerLoader(ResourceManager* r, sf::Vector2f size)
	: mResources(r)
{
	namespace fs = std::filesystem;

	//Iterate over all items in directory resource/towers
	for (auto& item : fs::directory_iterator("resource/towers"))
	{
		//If the extension is .json...
		std::string ext = item.path().extension().string();
		if (ext == ".json")
		{
			//Get the stem of the file
			//(a.k.a dart-monkey.json -> dart-monkey)
			std::string name = item.path().stem().string();

			//Load the tower and push it into the mTowers
			//vector.
			mTowers.emplace_back(r, name, size);
		}
	}
}

std::vector<Tower>& TowerLoader::getGuiTowers()
{
	return mTowers;
}

Tower& TowerLoader::getGuiTowerByName(std::string name)
{
	for (auto& tower : mTowers)
	{
		if (tower.getActualName() == name)
		{
			return tower;
		}
	}
	throw std::out_of_range("GUI Tower " + name + " not found.");
}

}