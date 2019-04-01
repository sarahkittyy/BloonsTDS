#include "AnimatedSprite.hpp"

AnimatedSprite::AnimatedSprite(sf::Texture& tex)
	: mTex(tex)
{
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
								  AnimatedSprite::Animation animation)
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
	auto anim = mAnimations.find(mCurrentAnimation);
	if (anim == mAnimations.end())
	{
		return;
	}

	Animation a = anim->second;

	if (mAnimationClock.getElapsedTime() >= sf::seconds(a.speed))
	{
		mAnimationClock.restart();
		mCurrentFrame++;
		if (mCurrentFrame >= a.frames.size())
		{
			mCurrentFrame = 0;
		}
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
	unsigned frame = mAnimations[mCurrentAnimation].frames[index];

	size_t tx = frame % mTexMapSize.x;
	size_t ty = frame / mTexMapSize.x;

	// clang-format off
	sf::Vector2u tex_size{
		mTex.getSize().x / mTexMapSize.x,
		mTex.getSize().y / mTexMapSize.y
	};
	// clang-format on

	size_t px = tx * tex_size.x;
	size_t py = ty * tex_size.y;

	mRect.setTextureRect(sf::IntRect(px, py, tex_size.x, tex_size.y));
	mRect.setSize({tex_size.x, tex_size.y});
}

sf::FloatRect AnimatedSprite::getGlobalBounds()
{
	return getTransform().transformRect(mRect.getGlobalBounds());
}