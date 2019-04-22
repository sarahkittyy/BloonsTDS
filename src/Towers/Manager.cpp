#include "Towers/Manager.hpp"

namespace Towers
{
Manager::Manager(ResourceManager& resources,
				 Economy& economy,
				 Tilemap::Renderer* renderer,
				 GUI::TowerLoader& gui_towerloader,
				 Bloons::Map& bloon_manager)
	: mResources(resources),
	  mEconomy(economy),
	  mGUITowerLoader(gui_towerloader),
	  mMapRenderer(renderer),
	  mMap(bloon_manager)
{
	mQueued = false;
}

Manager::HeldTower::HeldTower()
{
}

Manager::HeldTower::HeldTower(Tower* t, int r)
{
	tower.reset(t);
	setRangeState(false);
	range.setOutlineThickness(0);
	range.setRadius(r);
	range.setOrigin(range.getLocalBounds().width / 2.0f,
					range.getLocalBounds().height / 2.0f);
}

void Manager::HeldTower::update(sf::Vector2f mouse_pos)
{
	//Update the tower.
	tower->update();
	sf::FloatRect qbounds = tower->getGlobalBounds();
	tower->setPosition(mouse_pos.x - qbounds.width / 2.0f,
					   mouse_pos.y - qbounds.height / 2.0f);

	//Update the radius position.
	range.setPosition(tower->getPosition() +
					  sf::Vector2f(
						  tower->getGlobalBounds().width / 2.0f,
						  tower->getGlobalBounds().height / 2.0f));
}

void Manager::HeldTower::setRangeState(bool placeable)
{
	if (placeable)
	{
		range.setFillColor(sf::Color(127, 127, 127, 127));
	}
	else
	{
		range.setFillColor(sf::Color(200, 127, 127, 127));
	}
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
		if (mQueue.range.getRadius() >= 0)
		{
			target.draw(mQueue.range, states);
		}
		target.draw(*(mQueue.tower), states);
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
		sf::Vector2f mouse_pos = (sf::Vector2f)
			sf::Mouse::getPosition(mResources.getWindow());
		mQueue.update(mouse_pos);
	}

	//Check for any pressed hotkeys.
	for (auto& tower : mGUITowerLoader.getGuiTowers())
	{
		if (sf::Keyboard::isKeyPressed(tower.getHotkey()))
		{
			//If there's already a tower queued, assert
			//that it isn't the one we're clicking the hotkey for.
			if (!isQueued() || queuedTower().getName() != tower.getActualName())
			{
				queueTower(tower.getActualName());
			}
		}
	}

	//If there's a tower being placed right now.
	if (isQueued())
	{
		//Set the queue'd tower's range state.
		mQueue.setRangeState(isQueuePlaceable());

		//Escape if necessary.
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			unqueueTower();
		}
		//Otherwise, if we click somewhere...
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			//True if the shift key is held.
			bool shiftHeld = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);

			//If we can't place the queue'd tower,
			if (isQueuePlaceable())
			{
				//Force-Purchase the tower, and place it.
				mEconomy.purchase(queuedTower().getName(), true);
				placeQueuedTower();
			}

			//Unqueue if shift isn't held.
			if (!shiftHeld)
			{
				unqueueTower();
			}
		}
	}
}

bool Manager::isQueuePlaceable()
{
	///////////ASSERTIONS////////////
	//We have to be in the map's bounds.
	if (!mMapRenderer->isInBounds(getQueuedTowerBounds()))
	{
		return false;
	}
	//We have to be able to purchase it.
	else if (!mEconomy.canPurchase(queuedTower().getName()))
	{
		return false;
	}
	//It can't be on a track.
	else if (mMap.collidesPath(mQueue.tower->getGlobalBounds()))
	{
		return false;
	}
	//Iterate over all placed towers..
	for (auto& tower : mTowers)
	{
		//If any intersect, return false.
		if (tower.getGlobalBounds().intersects(mQueue.tower->getGlobalBounds()))
		{
			return false;
		}
	}

	//If none of the previous assertions failed, return true.
	return true;
}

void Manager::queueTower(std::string name)
{
	mQueued = true;

	//Get the texture of the tower.
	sf::Texture* tex = &mResources.texture("resource/towers/" + name + ".png");

	//Reset the queue'd tower.
	int radius = mGUITowerLoader.getGuiTowerByName(name).getRange();
	mQueue	 = HeldTower(new Tower(tex), radius);

	//Load the tower, passing references to the tower,
	//and texture for modification. Also pass the name
	//of the tower, for json loading purposes
	Towers::loadTowerFromName(*(mQueue.tower), tex, name);

	//Just place it offscreen for the first frame,
	//so it doesn't appear in the wrong spot until
	//it updates & moves to the mouse.
	mQueue.tower->setPosition({-100, -100});
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
	return mQueue.tower->getGlobalBounds();
}

const Tower& Manager::queuedTower()
{
	return *(mQueue.tower);
}

void Manager::placeQueuedTower()
{
	mTowers.push_back(*(mQueue.tower));
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