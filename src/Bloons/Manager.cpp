#include "Bloons/Manager.hpp"

namespace Bloons
{

Manager::Manager(std::vector<Path>& paths)
{
	mPaths	 = paths;
	mPathIndex = 0;
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

void Manager::sendBloon(Bloon& b)
{
	//We call this each bloon send to assert that each path
	//is traversed as equally as possible.
	nextPath();
	// clang-format off

	//Push the bloon.
	mBloons.push_back({
		.r = Renderer(b.getName()), //Set the renderer to the bloon.
		.path = getPath(), //Set the path for the bloon
		.bloon = b, //A copy of the bloon itself.
		.alive = true //Bloon starts out alive
	});
	// clang-format on

	//Assert we have started the path.
	mBloons.back().path.start();
	//Move the bloon to the first node's position.
	mBloons.back().r.setPosition(getPath().get().pos);
	//Set the next node to, well, the next node.
	mBloons.back().path.next();
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