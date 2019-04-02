#pragma once

#include <SFML/System.hpp>

#include <unordered_map>
#include <vector>

namespace Bloons
{

/**
 * @brief Defines a linear path for bloons to travel across. Linked-list structure.
 * 
 * @remarks Iterate in a while loop
 * 
 */
class Path
{
public:
	/**
	 * @brief The node itself. Defines a point on the path.
	 * 
	 */
	struct Node
	{
		sf::Vector2f pos;
	};

	/**
	 * @brief Default Constructor.
	 * 
	 */
	Path();

	/**
	 * @brief Add a node to the path.
	 * 
	 * @param n The node to append.
	 */
	void addNode(Node n);

	/**
	 * @brief Pop the last added node.
	 * 
	 * @return Node A copy of the popped node.
	 */
	Node popNode();

	/**
	 * @brief Resets the path psuedo-iterator, setting the index to 0.
	 * 
	 * @return int 0
	 */
	int start();

	/**
	 * @brief Move the internal pointer to the next node, for get().
	 * 
	 * @return int The index of the current node.
	 */
	int next();

	/**
	 * @brief Return the currently indexed node.
	 * 
	 * @return Node The node at the current index.
	 */
	Node get();

	/**
	 * @brief Get the ending position of the path.
	 * 
	 * @return int How many nodes there are.
	 * 
	 * @remarks Use next() while next() != end().
	 */
	int end();

private:
	/**
	 * @brief Internal vector of nodes.
	 * 
	 */
	std::vector<Node> nodes;

	/**
	 * @brief The current selected node.
	 * 
	 */
	size_t index;
};

/*
Example Code:
path.start();
while(path.next() != path.end())
{
	Node c = path.get();
	...
}
*/

}