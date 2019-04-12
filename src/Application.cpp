#include "Application.hpp"

sf::Vector2u Application::WINDOW_SIZE(800, 600);

Application::Application()
	: mWindow(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "Bloons TDS"),
	  mTowerManager(mResources)
{
	srand(time(NULL));

	mWindow.setFramerateLimit(60);

	//Init ImGui.
	ImGui::SFML::Init(mWindow);

	//Init the map renderer.
	Tilemap::loadGraphicsFromMap(mResources,
								 mMapRenderer,
								 "resource/maps/map.json");

	//Init the bloon loader.
	Bloons::Loader::init(mResources);

	//Init the bloon map.
	mMap.init("map");

	//mTowerManager.placeTower({.name = "dart-monkey", .pos = {100, 100}});
}

int Application::run()
{
	//ImGui timing clock
	sf::Clock ImGuiClock;

	mMap.runWave(0);

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
		mMap.update();
		mTowerManager.update();

		//

		//Update ImGui.
		ImGui::SFML::Update(mWindow, ImGuiClock.restart());

		//Render ImGui Components
		renderGui();

		//End ImGui drawing.
		ImGui::EndFrame();

		//Begin drawing.
		mWindow.clear(sf::Color(109, 83, 43));

		mWindow.draw(mMapRenderer);
		mWindow.draw(mTowerManager);
		mWindow.draw(mMap);

		//Draw ImGui
		ImGui::SFML::Render(mWindow);
		//Finish drawing.
		mWindow.display();
	}

	//Release resources.
	ImGui::SFML::Shutdown();

	return 0;
}

void Application::renderGui()
{
	//Flags for a static, non-moving imgui window.
	const ImGuiWindowFlags STATIC_FLAGS =
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoScrollbar |
		ImGuiWindowFlags_NoSavedSettings;

	sf::FloatRect mapBounds = mMapRenderer.getMapBounds();

	//Set the tower selection gui position & size.
	ImGui::SetNextWindowPos(ImVec2(
		0,
		mapBounds.height));
	ImGui::SetNextWindowSize(ImVec2(
		mapBounds.width,
		WINDOW_SIZE.y - mapBounds.height));
	//Tower Selection GUI.
	ImGui::Begin("Towers", nullptr, STATIC_FLAGS);



	ImGui::End();

	//Positioning for the start-wave gui window.
	ImGui::SetNextWindowPos(ImVec2(
		mapBounds.width,
		mapBounds.height));
	ImGui::SetNextWindowSize(ImVec2(
		WINDOW_SIZE.x - mapBounds.width,
		WINDOW_SIZE.y - mapBounds.height));
	//The start wave gui window.
	ImGui::Begin("Wave", nullptr, STATIC_FLAGS | ImGuiWindowFlags_NoTitleBar);



	ImGui::End();

	//Positioning for the status & upgrades window.
	ImGui::SetNextWindowPos(ImVec2(
		mapBounds.width,
		0));
	ImGui::SetNextWindowSize(ImVec2(
		WINDOW_SIZE.x - mapBounds.width,
		mapBounds.height));
	//Stats & upgrades window.
	ImGui::Begin("Stats", nullptr, STATIC_FLAGS);



	ImGui::End();
}