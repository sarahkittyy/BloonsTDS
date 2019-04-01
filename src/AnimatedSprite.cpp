#include "AnimatedSprite.hpp"

AnimatedSprite::AnimatedSprite(sf::Texture& tex)
	: mTex(tex)
{
	//Initialize default settings.
	mRect.setTexture(&mTex, true);
	mTexMapSize = {1, 1};
	resetAnimation();
}

void AnimatedSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mRect, states);
}

void AnimatedSprite::setTextureMapSize(sf::Vector2u size)
{
	mTexMapSize = size;
	resetAnimation();
}

void AnimatedSprite::addAnimation(std::string name,
								  Animation animation)
{
	mAnimations[name] = animation;
}

void AnimatedSprite::setAnimation(std::string name)
{
	mCurrentAnimation = name;
	resetAnimation();
}

void AnimatedSprite::update()
{
	//Attempt to find the current animation.
	auto anim = mAnimations.find(mCurrentAnimation);
	if (anim == mAnimations.end())
	{
		return;
	}

	Animation a = anim->second;

	//If it's frozen, just return.
	if (a.speed = -1)
	{
		return;
	}

	//If it's ready to update...
	if (mAnimationClock.getElapsedTime() >= sf::seconds(a.speed))
	{
		//Restart the clock, increment the frame.
		mAnimationClock.restart();
		mCurrentFrame++;
		//Loop the frame back to 0 if necessary.
		if (mCurrentFrame >= a.frames.size())
		{
			mCurrentFrame = 0;
		}

		//Move the rect index over to the current frame.
		setRectIndex(mCurrentFrame);
	}
}

void AnimatedSprite::resetAnimation()
{
	mAnimationClock.restart();
	mCurrentFrame = 0;
	if (mAnimations.empty())
	{
		return;
	}

	setRectIndex(0);
}

void AnimatedSprite::setRectIndex(size_t index)
{
	//Get the current frame from the index.
	unsigned frame = mAnimations[mCurrentAnimation].frames[index];

	//Get the texture x and y position.
	size_t tx = frame % mTexMapSize.x;
	size_t ty = frame / mTexMapSize.x;

	// clang-format off
	
	//Get the actual sprite size.
	sf::Vector2u tex_size{
		mTex.getSize().x / mTexMapSize.x,
		mTex.getSize().y / mTexMapSize.y
	};
	// clang-format on

	//Get the x and y position inside the texture of the tile we want.
	size_t px = tx * tex_size.x;
	size_t py = ty * tex_size.y;

	//Set the rect to focus on that position & size.
	mRect.setTextureRect(sf::IntRect(px, py, tex_size.x, tex_size.y));
	mRect.setSize({tex_size.x, tex_size.y});
}

sf::FloatRect AnimatedSprite::getGlobalBounds()
{
	return getTransform().transformRect(mRect.getGlobalBounds());
}