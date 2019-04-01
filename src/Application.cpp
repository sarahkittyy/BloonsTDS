#include "Application.hpp"

sf::Vector2u Application::WINDOW_SIZE(800, 600);

Application::Application()
	: mWindow(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "Bloons TDS")
{
	mWindow.setFramerateLimit(60);

	//Init ImGui.
	ImGui::SFML::Init(mWindow);

	//Init the map renderer.
	Tilemap::loadGraphicsFromMap(mMapRenderer,
								 "resource/map.json");

	mTowerManager.placeTower({.name = "dart-monkey", .pos = {100, 100}});
}

int Application::run()
{
	//ImGui timing clock
	sf::Clock ImGuiClock;

	//Main application loop.
	while (mWindow.isOpen())
	{
		//Process events.
		sf::Event event;
		while (mWindow.pollEvent(event))
		{
			//imgui events
			ImGui::SFML::ProcessEvent(event);
			//sfml events
			switch (event.type)
			{
			default:
				break;
			case sf::Event::Closed:
				mWindow.close();
			case sf::Event::Resized:
				WINDOW_SIZE = {event.size.width, event.size.height};
				mWindow.setSize(WINDOW_SIZE);
				break;
			}
		}

		//Regular Updates.
		mTowerManager.update();

		//

		//Update ImGui.
		ImGui::SFML::Update(mWindow, ImGuiClock.restart());



		//End ImGui drawing.
		ImGui::EndFrame();

		//Begin drawing.
		mWindow.clear(sf::Color::White);

		mWindow.draw(mMapRenderer);
		mWindow.draw(mTowerManager);

		//Draw ImGui
		ImGui::SFML::Render(mWindow);
		//Finish drawing.
		mWindow.display();
	}

	//Release resources.
	ImGui::SFML::Shutdown();

	return 0;
}
