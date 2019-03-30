#include "Tilemap/Renderer.hpp"

namespace Tilemap
{

Renderer::Renderer()
{
	//Init default settings.
	mSettings = {
		{"in_tile_size", std::array<int, 2>{16, 16}},
		{"out_tile_size", std::array<int, 2>{16, 16}},
		{"grid_size", std::array<int, 2>{40, 40}},
		{"texture_path", "resource/tilemap.png"},
		{"tiles", std::vector<int>()}};

	mVertices.setPrimitiveType(sf::Quads);
}

void Renderer::options(nlohmann::json settings)
{
	//Iterate through each setting, changing the internal settings
	for (auto& entry : settings.items())
	{
		mSettings[entry.key()] = entry.value();
	}
}

void Renderer::init()
{
	//Map settings to usable values.
	sf::Vector2u tex_tile_size{
		mSettings["in_tile_size"][0].get<unsigned>(),
		mSettings["in_tile_size"][1].get<unsigned>()};

	sf::Vector2u tile_size{
		mSettings["out_tile_size"][0].get<unsigned>(),
		mSettings["out_tile_size"][1].get<unsigned>()};

	sf::Vector2u grid_size{
		mSettings["grid_size"][0].get<unsigned>(),
		mSettings["grid_size"][1].get<unsigned>()};

	std::vector<unsigned> tiles = mSettings["tiles"];

	//Load the texture.
	mTex.loadFromFile(mSettings["texture_path"]
						  .get<std::string>());

	//Get texture information.
	sf::Vector2i texture_size{
		(unsigned)mTex.getSize().x / tex_tile_size.x,
		(unsigned)mTex.getSize().y / tex_tile_size.y};

	//Iterate through each tile.
	unsigned index = 0;
	for (auto& value : mSettings["tiles"].get<std::vector<unsigned>>())
	{
		//Get the rendered position of the current tile.
		sf::Rect<unsigned> pos;
		pos.left   = (index % grid_size.x) * tile_size.x;
		pos.top	= (index / grid_size.x) * tile_size.y;
		pos.width  = tile_size.x;
		pos.height = tile_size.y;

		//Get the texture coordinates of
		sf::Rect<unsigned> tex;
		tex.left   = (value % texture_size.x) * tex_tile_size.x;
		tex.top	= (value / texture_size.x) * tex_tile_size.y;
		tex.width  = tex_tile_size.x;
		tex.height = tex_tile_size.y;

		//Create the four vertices.
		mVertices.append(sf::Vertex(
			sf::Vector2f(pos.left, pos.top),
			sf::Vector2f(tex.left, tex.top)));
		mVertices.append(sf::Vertex(
			sf::Vector2f(pos.left + pos.width, pos.top),
			sf::Vector2f(tex.left + tex.width, tex.top)));
		mVertices.append(sf::Vertex(
			sf::Vector2f(pos.left + pos.width, pos.top + pos.height),
			sf::Vector2f(tex.left + tex.width, tex.top + tex.height)));
		mVertices.append(sf::Vertex(
			sf::Vector2f(pos.left, pos.top + pos.height),
			sf::Vector2f(tex.left, tex.top + tex.height)));

		index++;
	}
}

void Renderer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.texture = &mTex;
	states.transform *= getTransform();
	target.draw(mVertices, states);
}

}