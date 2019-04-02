#pragma once

#include <string>
#include <vector>

namespace Bloons
{

/**
 * @brief Defines the properties of a single bloon.
 * 
 */
class Bloon
{
public:
	/**
	 * @brief An inside of this bloon, inclding a name and a count
	 * representing another bloon.
	 * 
	 */
	struct Inside
	{
		std::string name;
		size_t ct;
	};

	/**
	 * @brief Set the speed of the bloon.
	 * 
	 * @param newSpeed the new speed.
	 */
	void setSpeed(float newSpeed);

	/**
	 * @brief Get the bloon speed.
	 * 
	 * @return float The speed of the bloon.
	 */
	float getSpeed();

	/**
	 * @brief Set the bloon name.
	 * 
	 * @param newName The new name of the bloon.
	 */
	void setName(std::string newName);

	/**
	 * @brief Get the bloon name.
	 * 
	 * @return std::string The name of the bloon.
	 */
	std::string getName();

	/**
	 * @brief Add an inside for this bloon to drop when popped.
	 * 
	 * @param in A bloon inside.
	 */
	void addInside(Inside in);

	/**
	 * @brief Remove all insides this bloon would drop from it.
	 * 
	 */
	void clearInsides();

	/**
	 * @brief Get the list of all insides this bloon drops upon popping.
	 * 
	 * @return const std::vector<Inside>& A constant reference to the insides of this bloon.
	 */
	const std::vector<Inside>& getInsides();

private:
	/**
	 * @brief The speed of the bloon.
	 * 
	 */
	float mSpeed;

	/**
	 * @brief The insides dropped upon this bloon being popped.
	 * 
	 */
	std::vector<Inside> mInsides;

	/**
	 * @brief The name of this bloon.
	 * 
	 */
	std::string mName;
};

}