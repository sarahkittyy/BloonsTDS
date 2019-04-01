#pragma once

#include <SFML/Graphics.hpp>

#include <string>
#include <unordered_map>

/**
 * @brief A simple animated sprite class, for defining and running custom animations.
 * 
 */
class AnimatedSprite : public sf::Drawable, public sf::Transformable
{
public:
	/**
	 * @brief The animation structure, with a list of frames to run
	 * sequentially, and a speed (seconds) at which they run at.
	 * 
	 */
	struct Animation
	{
		std::vector<unsigned> frames{};
		float speed = 1;
	};

	/**
	 * @brief Construct a new Animated Sprite.
	 * 
	 * @param tex The texture of the sprite.
	 */
	AnimatedSprite(sf::Texture& tex);

	/**
	 * @brief Set the size of the grid of the texture.
	 * 
	 * @param size The texture's grid size, i.e. 2x2 for 4 frames of animation.
	 */
	void setTextureMapSize(sf::Vector2u size);

	/**
	 * @brief Get the bounds of the sprite.
	 * 
	 * @return sf::FloatRect The global boundaries of the sprite.
	 */
	sf::FloatRect getGlobalBounds();

	/**
	 * @brief Add an animation to the animation dictionary.
	 * 
	 * @param name The name of the animation.
	 * @param animation The animation data itself.
	 */
	void addAnimation(std::string name, Animation animation);

	/**
	 * @brief Set the currently looping animation.
	 * 
	 * @param name The name of the animation.
	 */
	void setAnimation(std::string name);

	/**
	 * @brief Update the sprite. Call once per frame.
	 * 
	 */
	void update();

private:
	/**
	 * @brief SFML's draw() override.
	 *  
	 */
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	/**
	 * @brief Resets the sprite's animation.
	 * 
	 */
	void resetAnimation();

	/**
	 * @brief Set the texture rect over the given index.
	 * 
	 * @param index The index into the texture map to use.
	 */
	void setRectIndex(size_t index);

	/**
	 * @brief The texture of the rect.
	 * 
	 */
	sf::Texture& mTex;

	/**
	 * @brief The rectangle itself.
	 * 
	 */
	sf::RectangleShape mRect;

	/**
	 * @brief The internal timer for timing animations.
	 * 
	 */
	sf::Clock mAnimationClock;

	/**
	 * @brief The map of names -> animations.
	 * 
	 */
	std::unordered_map<std::string, Animation> mAnimations;

	/**
	 * @brief The animation currently playing.
	 * 
	 */
	std::string mCurrentAnimation;

	/**
	 * @brief The frame of the current animation.
	 * 
	 */
	size_t mCurrentFrame;

	/**
	 * @brief The size of the grid of textures in the texture map.
	 * 
	 */
	sf::Vector2u mTexMapSize;
};