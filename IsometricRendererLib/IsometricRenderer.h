#pragma once

#include <AbstractRenderer.h>
#include <Environment.h>
#include <BaseCharacterModel.h>
#include "CellColorator.h"

#include <vector>
#include <SFML\Graphics.hpp>

namespace tw
{
	class CharacterView;

	class IsometricRenderer : public AbstractRenderer
	{
		sf::RenderWindow * window;
		CellColorator * colorator;

		std::map<BaseCharacterModel*, CharacterView*> characterViewsCache;
		CharacterView & getCharacterView(BaseCharacterModel * model);

		void manageEvents(Environment * environment, std::vector<BaseCharacterModel*> & characters);

	public:
		IsometricRenderer(sf::RenderWindow * window);
		inline void modifyWindow(sf::RenderWindow * newWindow) { this->window = newWindow; }
		virtual void render(Environment* environment, std::vector<BaseCharacterModel*> & characters, float deltatime);

		void setColorator(CellColorator * colorator)
		{
			this->colorator = colorator;
		}
	};
}