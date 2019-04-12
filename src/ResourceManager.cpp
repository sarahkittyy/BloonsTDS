#include "ResourceManager.hpp"

ResourceManager::ResourceManager(sf::RenderWindow* window)
	: mWindow(window)
{
}

const sf::RenderWindow& ResourceManager::getWindow()
{
	return *mWindow;
}

sf::Texture& ResourceManager::texture(std::string path)
{
	auto found = mTextures.find(path);
	if (found == mTextures.end())
	{
		mTextures[path] = sf::Texture();
		mTextures[path].loadFromFile(path);
		return mTextures[path];
	}
	else
	{
		return found->second;
	}
}