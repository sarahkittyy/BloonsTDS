#pragma once

#include <SFML/Graphics.hpp>

#include "AnimatedSprite.hpp"

namespace Towers
{

/**
 * @brief Tower class, stores the sprite along with extra information about the tower.
 * 
 */
class Tower : public sf::Drawable, public sf::Transformable
{
public:
	/**
	 * @brief An upgrade's data structure.
	 * 
	 */
	struct Upgrade
	{
		std::string name;
		AnimatedSprite::Animation anim;
		std::string next;
	};

	/**
	 * @brief Construct the tower from the given texture.
	 * 
	 * @param tex The texture to use with the tower.
	 */
	Tower(sf::Texture* tex);

	/**
	 * @brief Virtual destructor for any inheritance.
	 * 
	 */
	virtual ~Tower();

	/**
	 * @brief Updates the tower. 
	 * 
	 */
	virtual void update();

	/**
	 * @brief Set the name of the tower.
	 * 
	 */
	void setName(std::string name);

	/**
	 * @brief Get the name of the tower.
	 * 
	 * @return std::string The name of the tower.
	 */
	std::string getName() const;

	/**
	 * @brief Set the Texture of the internal animated sprite.
	 * 
	 * @param tex 
	 */
	void setTexture(sf::Texture* tex);

	/**
	 * @brief Add an upgrade to the tower, with a corresponding animation.
	 * 
	 * @param upgrade The upgrade to add.
	 */
	void addUpgrade(Upgrade upgrade);

	/**
	 * @brief Set the tower to the current upgrade.
	 * 
	 * @param name The name of the upgrade.
	 * 
	 * @see Tower::addUpgrade(..)
	 */
	void setUpgrade(std::string name);

	/**
	 * @brief Tries to upgrade the tower. If we're on the last upgrade,
	 * returns false.
	 * 
	 */
	bool upgrade();

	/**
	 * @brief Wrapper for AnimatedSprite::setTextureMapSize.
	 * 
	 * @param size The size of the texture's sprite map.
	 */
	void setTextureMapSize(sf::Vector2u size);

	/**
	 * @brief Get the Global Bounds of the tower.
	 * 
	 * @return sf::FloatRect The boundary rectangle of the tower sprite.
	 */
	sf::FloatRect getGlobalBounds();

private:
	/**
	 * @brief SFML's draw() override.
	 * 
	 */
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	/**
	 * @brief Pointer to the texture of the tower.
	 * 
	 */
	sf::Texture* mTex;

	/**
	 * @brief The name of the tower.
	 * 
	 */
	std::string mName;

	/**
	 * @brief An unordered vector of this tower's upgrades.
	 * 
	 */
	std::vector<Upgrade> mUpgrades;

	/**
	 * @brief The index in mUpgrades of the currently drawn upgrade.
	 * 
	 */
	size_t mCurrentUpgrade;

	/**
	 * @brief The sprite of the tower itself.
	 * 
	 */
	AnimatedSprite mSprite;
};

}