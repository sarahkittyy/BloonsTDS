#include "Towers/Manager.hpp"

namespace Towers
{

Manager::Manager()
{
}

void Manager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& tower : mTowers)
	{
		target.draw(tower, states);
	}
}

void Manager::update()
{
	for (auto& tower : mTowers)
	{
		tower.update();
	}
}

void Manager::placeTower(TowerFramework framework)
{
	sf::Texture& tex = getTexture(framework.name);
	mTowers.push_back(Tower(&tex));
	Tower& t = mTowers[mTowers.size() - 1];
	Towers::loadTowerFromName(t, &tex, framework.name);
	t.setPosition(framework.pos);
}

sf::Texture& Manager::getTexture(std::string key)
{
	auto found = mResources.find(key);
	if (found == mResources.end())
	{
		mResources[key] = sf::Texture();
		return mResources[key];
	}
	else
	{
		return found->second;
	}
}

}