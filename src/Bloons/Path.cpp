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

}