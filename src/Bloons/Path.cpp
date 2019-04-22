#include "Bloons/Path.hpp"

namespace Bloons
{

Path::Path()
{
	mIndex = 0;
}

void Path::addNode(Path::Node n)
{
	mNodes.push_back(n);
}

Path::Node Path::popNode()
{
	if (mNodes.size() == 0)
	{
		throw std::out_of_range("Cannot pop node off empty path!");
	}
	else
	{
		//Copy last element.
		Node cpy = mNodes[mNodes.size() - 1];
		//Pop last element
		mNodes.pop_back();
		//Return
		return cpy;
	}
}

int Path::start()
{
	mIndex = 0;
	return 0;
}

int Path::next()
{
	return ++mIndex;
}

void Path::set(int index)
{
	mIndex = index;
}

Path::Node Path::get()
{
	return mNodes[mIndex];
}

int Path::index()
{
	return mIndex;
}

Path::Node Path::at(int index)
{
	return mNodes[index];
}

int Path::end()
{
	return mNodes.size();
}

std::vector<sf::FloatRect> Path::getPathBounds(float factor)
{
	std::vector<sf::FloatRect> ret;

	//For every two sequential nodes..
	for (unsigned i = 0; i < mNodes.size() - 1; ++i)
	{
		Node n1, n2;
		n1 = mNodes[i];
		n2 = mNodes[i + 1];

		//Multiply their positions by the factor.
		n1.pos.x *= factor;
		n1.pos.y *= factor;
		n2.pos.x *= factor;
		n2.pos.y *= factor;

		//Push the corresponding rect.
		ret.push_back(sf::FloatRect(
			n1.pos.x,
			n1.pos.y,
			n2.pos.x - n1.pos.x + factor,
			n2.pos.y - n1.pos.y + factor));
	}

	return ret;
}

bool Path::collides(sf::FloatRect bounds, float factor)
{
	//Get the path collision.
	auto f = getPathBounds(factor);

	//If the bounds collide with any of the rects, return true.
	for (auto& rect : f)
	{
		if (rect.intersects(bounds))
		{
			return true;
		}
	}
	//Otherwise, return false.
	return false;
}

}