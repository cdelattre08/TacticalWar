#pragma once

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

namespace tw
{
	class Screen
	{
	private:
		float deltatime;

	protected:
		float getDeltatime() {
			return deltatime;
		}

	public:
		Screen();
		virtual void handleEvents(sf::RenderWindow * window, tgui::Gui * gui) = 0;
		virtual void update(float deltatime) {
			this->deltatime = deltatime;
		}
		virtual void render(sf::RenderWindow * window) = 0;
	};
}