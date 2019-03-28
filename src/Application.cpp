#include "Application.hpp"

sf::Vector2u Application::WINDOW_SIZE(600, 600);

Application::Application()
	: mWindow(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "Bloons TDS")
{
	mWindow.setFramerateLimit(60);

	//Init ImGui.
	ImGui::SFML::Init(mWindow);
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

		//Update ImGui.
		ImGui::SFML::Update(mWindow, ImGuiClock.restart());

		ImGui::Begin("yeet");
		ImGui::Text("%d", WINDOW_SIZE.x);
		ImGui::End();

		//End ImGui drawing.
		ImGui::EndFrame();

		//Begin drawing.
		mWindow.clear(sf::Color::White);

		//Draw ImGui
		ImGui::SFML::Render(mWindow);
		//Finish drawing.
		mWindow.display();
	}

	//Release resources.
	ImGui::SFML::Shutdown();

	return 0;
}
