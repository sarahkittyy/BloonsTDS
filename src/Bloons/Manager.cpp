#include "Bloons/Manager.hpp"

namespace Bloons
{

Manager::Manager(std::vector<Path>& paths,
				 unsigned tileSize)
{
	mPaths	 = paths;
	mTileSize  = tileSize;
	mPathIndex = 0;
}

void Manager::setTileSize(unsigned tileSize)
{
	mTileSize = tileSize;
}

void Manager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//Draw all rendered bloons.
	for (auto& i : mBloons)
	{
		target.draw(i.r, states);
	}
}

void Manager::runWave(Wave w)
{
	//Copy the wave.
	mCurrentWave = w;
	//Set the send-bloon callback.
	mCurrentWave.setBloonCallback([this](Bloon& b) {
		this->sendBloon(b);
	});

	//Start the current wave.
	mCurrentWave.start();
}

void Manager::update()
{
	//If there's a running wave..
	if (mCurrentWave.isStarted())
	{
		//Update it..
		mCurrentWave.update();

		//Clear the bloon queue.
		clearQueue();

		//Update each bloon.
		for (auto& bloon : mBloons)
		{
			bloon.r.update();

			//The bloon's speed..
			float speed = bloon.bloon.getSpeed();

			//Initial and target positions.
			sf::Vector2f pos  = bloon.r.getPosition();
			sf::Vector2f next = bloon.path.get().pos;

			//Get the x/y dist to the next node.
			sf::Vector2f d = dist(pos, next);

			//If we're close enough to the target position.
			if (d.x < speed && d.x > -speed && d.y < speed && d.y > -speed)
			{
				//We can snap to it, and go to the next node.
				bloon.r.setPosition(bloon.path.get().pos);

				//If we've reached the end...
				if (bloon.path.next() == bloon.path.end())
				{
					//We're done.
					bloon.alive = false;
				}
			}
			else   //If we're still moving.
			{
				//Get the x & y unit vector.
				d.x = d.x / std::hypot(d.x, d.y);
				d.y = d.y / std::hypot(d.x, d.y);

				//Let the magnitude be the speed.
				d.x *= speed;
				d.y *= speed;

				//Move the bloon.
				bloon.r.move(d);
			}
		}
		//Handle popped bloons.
		for (auto bloon = mBloons.begin();
			 bloon != mBloons.end(); ++bloon)
		{
			if (!bloon->popped)
			{
				continue;
			}   //Only deal with popped bloons.

			//Iterate over each inner bloon..
			auto insides = bloon->bloon.getInsides();
			for (auto& inner : insides)
			{
				//Get the distribution of bloons.
				/*
				Bloons should be around 5 px apart,
				so we should let the random function
				get values between +/- 5*inner.ct
				*/
				int dist = 10 * ((inner.ct - 1) / 2);
				dist	 = (dist > 15) ? (15) : (dist);
				//..
				for (size_t i = 0; i < inner.ct; ++i)
				{
					//Load a bloon sprite for it.
					BloonSprite& bl = createBloon(Loader::getBloon(inner.name), &mBloonQueue);
					//Set it's position & path identical
					//to the current bloon.
					bl.path = bloon->path;
					//Move the bloon to the new position.
					bl.r.setPosition(bloon->r.getPosition());

					//Shift it around a little, as it was popped.
					long shiftX =
						(dist == 0) ? (0)
									: (rand() % (2 * dist) - dist);
					long shiftY =
						(dist == 0) ? (0)
									: (rand() % (2 * dist) - dist);

					bl.r.move(shiftX, shiftY);
				}
			}

			//Set the bloon to dead.
			bloon->alive = false;
		}
		//Erase dead bloons.
		for (auto bloon = mBloons.begin(); bloon != mBloons.end();)
		{
			if (!bloon->alive)
			{
				mBloons.erase(bloon);
			}
			else
			{
				bloon++;
			}
		}
	}
	else if (mBloons.size() == 0 && mCurrentWave.isDone())   //If there's no bloons left, stop the wave.
	{
		mCurrentWave.stop();
	}
}

bool Manager::collidesPath(sf::FloatRect bounds)
{
	//For every path...
	for (auto& path : mPaths)
	{
		//Return true if the path collides with the bounds.
		if (path.collides(bounds, (float)mTileSize))
		{
			return true;
		}
	}

	//False if no path collided.
	return false;
}

void Manager::clearQueue()
{
	for (auto& bloon : mBloonQueue)
	{
		mBloons.push_back(bloon);
	}
	mBloonQueue.clear();
}

Manager::BloonSprite&
Manager::createBloon(Bloon& b,
					 std::vector<BloonSprite>* dest)
{
	//Create the bloon.
	dest->push_back({
		.r		= Renderer(b.getName()),   //Set the renderer to the bloon.
		.path   = getPath(),			   //Set the path for the bloon
		.bloon  = b,					   //A copy of the bloon itself.
		.alive  = true,					   //Bloon starts out alive.
		.popped = false					   //Bloon is not popped yet.
	});

	//Return it.
	return dest->back();
}

void Manager::sendBloon(Bloon& b)
{
	//We call this each bloon send to assert that each path
	//is traversed as equally as possible.
	nextPath();

	//Push the bloon.
	BloonSprite& bl = createBloon(b, &mBloons);

	//Assert we have started the path.
	bl.path.start();
	//Move the bloon to the first node's position.
	bl.r.setPosition(getPath().get().pos);
	//Set the next node to, well, the next node.
	bl.path.next();
}

void Manager::nextPath()
{
	//Increment the path index, switching the path we take evenly.
	mPathIndex++;
	//Loop back to the first path if we reach the end of the list
	//of paths.
	if (mPathIndex >= mPaths.size())
	{
		mPathIndex = 0;
	}
}

Path Manager::getPath()
{
	return mPaths[mPathIndex];
}

sf::Vector2f Manager::dist(sf::Vector2f now, sf::Vector2f next)
{
	return sf::Vector2f(
		next.x - now.x,
		next.y - now.y);
}

}