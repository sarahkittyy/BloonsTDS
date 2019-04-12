#include "Towers/Manager.hpp"

namespace Towers
{
Manager::Manager(ResourceManager& resources)
	: mResources(resources)
{
	mQueued = false;
}

void Manager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//Draw all towers.
	for (auto& tower : mTowers)
	{
		target.draw(tower, states);
	}
	//Draw the queued tower if necessary.
	if (mQueued)
	{
		target.draw(*mQueue, states);
	}
}

void Manager::update()
{
	//Update all towers.
	for (auto& tower : mTowers)
	{
		tower.update();
	}
	//Update the queued tower if necessary.
	if (mQueued)
	{
		mQueue->update();

		sf::Vector2f mouse_pos = (sf::Vector2f)
			sf::Mouse::getPosition(mResources.getWindow());

		sf::FloatRect qbounds = mQueue->getGlobalBounds();

		mQueue->setPosition(mouse_pos.x - qbounds.width / 2.0f,
							mouse_pos.y - qbounds.height / 2.0f);
	}
}

void Manager::queueTower(std::string name)
{
	mQueued = true;

	//Get the texture of the tower.
	sf::Texture* tex = &mResources.texture("resource/towers/" + name + ".png");

	//Reset the queue'd tower.
	mQueue.reset(new Tower(tex));

	//Load the tower, passing references to the tower,
	//and texture for modification. Also pass the name
	//of the tower, for json loading purposes
	Towers::loadTowerFromName(*mQueue, tex, name);

	//Just place it offscreen for the first frame,
	//so it doesn't appear in the wrong spot until
	//it updates & moves to the mouse.
	mQueue->setPosition({-100, -100});
}

void Manager::unqueueTower()
{
	mQueued = false;
}

bool Manager::isQueued()
{
	return mQueued;
}

sf::FloatRect Manager::getQueuedTowerBounds()
{
	return mQueue->getGlobalBounds();
}

const Tower& Manager::queuedTower()
{
	return *mQueue;
}

void Manager::placeQueuedTower()
{
	mQueued = false;
	mTowers.push_back(*mQueue);
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
	Tower& t = mTowers.back();

	//Load the tower, passing references to the tower,
	//and texture for modification. Also pass the name
	//of the tower, for json loading purposes
	Towers::loadTowerFromName(t, tex, framework.name);

	//Set the position of the tower.
	t.setPosition(framework.pos);
}

}