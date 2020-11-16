#pragma once

#include "Screen.h"

namespace tw
{
	class LoginScreen : public Screen
	{
	private:
		sf::Font font;
		sf::Text title;
		bool readyForConnect;

	public:
		LoginScreen(tgui::Gui * gui);

		virtual void handleEvents(sf::RenderWindow * window, tgui::Gui * gui);
		virtual void update(float deltatime);
		virtual void render(sf::RenderWindow * window);
	};
}