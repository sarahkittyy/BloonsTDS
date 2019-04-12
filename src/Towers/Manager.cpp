#include "Towers/Manager.hpp"

namespace Towers
{
Manager::Manager(ResourceManager& resources)
	: mResources(resources)
{
}

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

void Manager::placeTower(Manager::TowerFramework framework)
{
	//Get the texture of the tower.
	sf::Texture* tex = &mResources.texture("resource/towers/" + framework.name + ".png");

	//Push back a new tower, giving it the initial texture
	//This texture is just a placeholder, we will update it in
	//Towers::loadTowerFromName()...
	mTowers.emplace_back(tex);

	//Get the tower we just emplaced back.
	Tower& t = mTowers[mTowers.size() - 1];

	//Load the tower, passing references to the tower,
	//and texture for modification. Also pass the name
	//of the tower, for json loading purposes
	Towers::loadTowerFromName(t, tex, framework.name);

	//Set the position of the tower.
	t.setPosition(framework.pos);
}

}