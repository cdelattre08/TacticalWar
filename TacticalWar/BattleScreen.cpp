#include "BattleScreen.h"
#include "TestCharacterModel.h"
#include <Pathfinder.h>

using namespace tw;

BattleScreen::BattleScreen(tgui::Gui * gui)
{
	this->gui = NULL;
	this->window = NULL;
	
	gui->removeAllWidgets();
	
	renderer = new IsometricRenderer(NULL);
	environment = new Environment(11, 5, 0);
	environment->getMapData(2, 2)->setIsObstacle(true);
	environment->getMapData(1, 1)->setIsWalkable(false);

	colorator = new TWColorator(sf::Color(40, 200, 255));

	renderer->setColorator(colorator);
	renderer->addEventListener(this);

	characters.push_back(new TestCharacterModel(environment, 0, 0, 0));

	font.loadFromFile("./assets/font/arial.ttf");
	FPS.setFont(font);
}

void BattleScreen::handleEvents(sf::RenderWindow * window, tgui::Gui * gui)
{	
	this->window = window;
	this->gui = gui;
	/*
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();
		else if (event.type == sf::Event::Resized)
		{
			int sizeX = event.size.width;
			int sizeY = event.size.height;
			sf::View view = window->getView();
			view.setSize(event.size.width, event.size.height);
			window->setView(view);
		}

		gui->handleEvent(event);
	}	
	*/
}

void BattleScreen::update(float deltatime)
{
	Screen::update(deltatime);

	std::vector<Point2D> pathZone;
	for (int i = 0; i < characters.size(); i++)
	{
		characters[i]->update(deltatime);

		if (!characters[i]->hasTargetPosition())
		{
			//setNextPosition();
		}

		int x = characters[i]->getCurrentX();
		int y = characters[i]->getCurrentY();
		pathZone.push_back(Point2D(x - 1, y));
		pathZone.push_back(Point2D(x + 1, y));
		pathZone.push_back(Point2D(x, y - 1));
		pathZone.push_back(Point2D(x, y + 1));
	}

	colorator->setPathZone(pathZone);

	double fps = 1.0 / deltatime;
	FPS.setString(std::to_string((int)fps));
	FPS.setFillColor(sf::Color::Red);
	FPS.setPosition(10, 10);
}

void BattleScreen::render(sf::RenderWindow * window)
{
	renderer->modifyWindow(window);
	renderer->render(environment, characters, getDeltatime());
	window->draw(FPS);
}

// Renderer Event Listener
void BattleScreen::onCellClicked(int cellX, int cellY)
{
	std::cout << "Cell x=" << cellX << ", y=" << cellY << " clicked !" << std::endl;
	BaseCharacterModel * m = characters[0];
	if (!m->hasTargetPosition())
	{
		Point2D startPosition(m->getCurrentX(), m->getCurrentY());
		Point2D targetPosition(cellX, cellY);

		std::vector<Point2D> path = Pathfinder::getInstance()->getPath(startPosition, targetPosition, environment, std::vector<Obstacle*>());
		m->setPath(path);
	}
}

void BattleScreen::onCellHover(int cellX, int cellY)
{

}

void BattleScreen::onCellMouseDown(int cellX, int cellY)
{

}

void BattleScreen::onEvent(void * e)
{
	if (e != NULL)
	{
		sf::Event * event = (sf::Event*)e;

		if (event->type == sf::Event::Resized)
		{
			if (window != NULL)
			{
				int sizeX = event->size.width;
				int sizeY = event->size.height;
				sf::View view = window->getView();
				view.setSize(event->size.width, event->size.height);
				window->setView(view);
			}
		}

		if(gui != NULL)
			gui->handleEvent(*event);
	}
}
//----------------------------------------------------------