#include "pch.h"
#include "IsometricRenderer.h"
#include <CharacterView.h>

#include <iostream>

using namespace tw;

IsometricRenderer::IsometricRenderer(sf::RenderWindow * window)
{
	this->window = window;
	this->colorator = NULL;
}

void IsometricRenderer::manageEvents(Environment * environment, std::vector<BaseCharacterModel*> & characters)
{
	sf::Event e;
	while (window->pollEvent(e))
	{
		// check the type of the event...
		switch (e.type)
		{
			// window closed
		case sf::Event::Closed:
			window->close();
			break;

			// key pressed
		case sf::Event::KeyPressed:
			
			break;

		case sf::Event::MouseButtonPressed:
			if (e.mouseButton.button == sf::Mouse::Left)
			{
				int x = e.mouseButton.x;
				int y = e.mouseButton.y;

				int cellX = x / 64;
				int cellY = y / 64;

				if (cellX >= 0 && cellX < environment->getWidth()
					&&
					cellY >= 0 && cellY < environment->getHeight())
				{
					notifyCellClicked(cellX, cellY);
				}
			}
			break;
			// we don't process other types of events
		default:
			break;
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2i position = sf::Mouse::getPosition(*window);
		int cellX = position.x / 64;
		int cellY = position.y / 64;
		if (cellX >= 0 && cellX < environment->getWidth()
			&&
			cellY >= 0 && cellY < environment->getHeight())
		{
			notifyCellMouseDown(cellX, cellY);
		}
	}
}

void IsometricRenderer::render(Environment* environment, std::vector<BaseCharacterModel*> & characters, float deltatime)
{
	manageEvents(environment, characters);
	// TODO (team "Rendu graphique") : Réaliser le code de dessin de l'environnement (la map) et des personnages dans un repère isométrique.
	// Vous devrez calculer la position des tuiles à l'écran en fonction de leur position dans la grille (dans le tableau 2D)

	sf::RectangleShape rect;
	sf::Color color;
	sf::Vector2f size(64, 64);
	
	for (int i = 0; i < environment->getWidth(); i++)
	{
		for (int j = 0; j < environment->getHeight(); j++)
		{
			CellData * cell = environment->getMapData(i, j);
			if (cell->getIsObstacle())
			{
				color = sf::Color::Red;
			}
			else if (cell->getIsWalkable())
			{
				color = sf::Color::White;
			}
			else
			{
				color = sf::Color::Black;
			}
			
			rect.setPosition(i*64, j*64); // peut être ici qu'il faut changer le co TODO:: Trouver la valeur de "environment->getWidth
			rect.setSize(size);

			sf::Color mulColor = sf::Color::White;
			if (colorator != NULL)
			{
				mulColor = colorator->getColorForCell(cell);
			}

			rect.setFillColor(color * mulColor);

			window->draw(rect);
		}
	}
	
	for (int i = 0; i < characters.size(); i++)
	{
		BaseCharacterModel * m = characters[i];
		CharacterView & v = getCharacterView(m);
		v.update(deltatime);
		sf::Sprite * s = v.getImageToDraw();
		s->setPosition(m->getInterpolatedX() * 64, m->getInterpolatedY() * 64);


		sf::IntRect rect = s->getTextureRect();
		bool flipped = s->getScale().x < 0;
		float scaleX = 64.0 / (float)rect.width;
		float scaleY = 64.0 / (float)rect.height;
		s->setScale(flipped ? -scaleX : scaleX, scaleY);
		window->draw(*s);
	}
}


CharacterView & IsometricRenderer::getCharacterView(BaseCharacterModel * model)
{
	if (characterViewsCache.find(model) == characterViewsCache.end())
	{
		characterViewsCache[model] = new CharacterView(model);
	}

	return *characterViewsCache[model];
}