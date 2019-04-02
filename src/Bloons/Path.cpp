#include "Bloons/Path.hpp"

namespace Bloons
{

Path::Path()
{
	index = 0;
}

void Path::addNode(Path::Node n)
{
	nodes.push_back(n);
}

Path::Node Path::popNode()
{
	if (nodes.size() == 0)
	{
		throw std::out_of_range("Cannot pop node off empty path!");
	}
	else
	{
		//Copy last element.
		Node cpy = nodes[nodes.size() - 1];
		//Pop last element
		nodes.pop_back();
		//Return
		return cpy;
	}
}

int Path::start()
{
	index = 0;
	return 0;
}

int Path::next()
{
	return ++index;
}

Path::Node Path::get()
{
	return nodes[index];
}

int Path::end()
{
	return nodes.size();
}

}