#include "Towers/Manager.hpp"

namespace Towers
{
void Manager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//Draw all towers.
	for (auto& tower : mTowers)
	{
		target.draw(tower, states);
	}
}

void Manager::update()
{
	//Update all towers.
	for (auto& tower : mTowers)
	{
		tower.update();
	}
}

void Manager::placeTower(TowerFramework framework)
{
	//Get the texture of the tower.
	sf::Texture& tex = getTexture(framework.name);

	//Push back a new tower, giving it the initial texture
	//This texture is just a placeholder, we will update it in
	//Towers::loadTowerFromName()...
	mTowers.emplace_back(&tex);

	//Get the tower we just emplaced back.
	Tower& t = mTowers[mTowers.size() - 1];

	//Load the tower, passing references to the tower,
	//and texture for modification. Also pass the name
	//of the tower, for json loading purposes
	Towers::loadTowerFromName(t, &tex, framework.name);

	//Set the position of the tower.
	t.setPosition(framework.pos);
}

sf::Texture& Manager::getTexture(std::string key)
{
	//Try to find the texture.
	auto found = mResources.find(key);
	if (found == mResources.end())   //If it's not found...
	{
		//Create & return it.
		mResources[key] = sf::Texture();
		return mResources[key];
	}
	else   //Otherwise..
	{
		//Return the found texture.
		return found->second;
	}
}

}