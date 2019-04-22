#pragma once

#include <SFML/Graphics/Rect.hpp>
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
	 * @brief Set the path's current node.
	 * 
	 * @param index The node of the path.
	 */
	void set(int index);

	/**
	 * @brief Return the currently indexed node.
	 * 
	 * @return Node The node at the current index.
	 */
	Node get();

	/**
	 * @brief Return the current index.
	 * 
	 * @return int The index of the path.
	 */
	int index();

	/**
	 * @brief Get the node at the given index.
	 * 
	 * @param index The index.
	 * @return Node The node @ index.
	 */
	Node at(int index);

	/**
	 * @brief Get the ending position of the path.
	 * 
	 * @return int How many nodes there are.
	 * 
	 * @remarks Use next() while next() != end().
	 */
	int end();

	/**
	 * @brief Get a vector of FloatRects corresponding to the bounds of the path.
	 * 
	 * @param factor The width of each tile.
	 * @return std::vector<sf::FloatRect> A vector of path collisions.
	 */
	std::vector<sf::FloatRect> getPathBounds(float factor = 1);

	/**
	 * @brief Checks if the given boundaries collide with the path. 
	 * 
	 * @param factor The width of each tile, so path coords can be converted to boundaries.
	 * @param bounds The boundaries to check for collision.
	 * @return true If it collides.
	 */
	bool collides(sf::FloatRect bounds, float factor = 1);

private:
	/**
	 * @brief Internal vector of nodes.
	 * 
	 */
	std::vector<Node>
		mNodes;

	/**
	 * @brief The current selected node.
	 * 
	 */
	size_t mIndex;
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