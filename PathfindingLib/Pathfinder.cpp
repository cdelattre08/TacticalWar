#include "pch.h"
#include "Pathfinder.h"
#include <cstdlib>
#include <limits>
#include <math.h>


using namespace tw;

Pathfinder * Pathfinder::instance = NULL;

Pathfinder * Pathfinder::getInstance()
{
	if (instance == NULL)
		instance = new Pathfinder();

	return instance;
}

Pathfinder::Pathfinder()
{
}


Pathfinder::~Pathfinder()
{
}



int Pathfinder::TotalCostFromStartToEnd() //calcul du cout total du point de depart au point d'arrivee (heuristique)
{
	
}

Orientation Pathfinder::getOrientationFromPosition(Position p1, Position p2)
{
	// TODO : Implémenter le calcul de l'orientation du personnage à partir des positions passées en paramètres.
	// Les positions passées en paramètre représentent le mouvement du personnage de p1 vers p2.
	// A partir de ces deux positions, vous devez déterminer l'orientation résultante du mouvement.
	return Orientation::BOTTOM_RIGHT;
}

std::vector<Position> Pathfinder::getPath(Position startPosition, Position endPosition, Environment * environment, std::vector<Obstacle*> obstacles)
{
	std::vector<Position> path;

	std::vector<CellData*> P;
	std::map<CellData*, float> d;
	

	for (int i = 0; i < environment->getWidth(); i++)
	{
		for (int j = 0; j < environment->getHeight(); j++)
		{
			CellData * cell = environment->getMapData(i, j);
			Obstacle* cell_target;


			if (!cell->getIsObstacle() && cell_target->getIsTargettable)
			{
				d[cell] = std::numeric_limits<float>::max(); //sommet à +infini
			}
		}
	}

	d[environment->getMapData(startPosition.getX(), startPosition.getY())] = 0;
	CellData * cell;
	float PlusCourteDistance = std::numeric_limits<float>::max();
	float NewDistance;

	while(P.size != d.size)	//on itère tant que qu'il existe un sommet hors de P donc tant que P ne fait pas la même taille que le nombre total de sommets
	{
		CellData * a = NULL;
		for (int i = 0; i < environment->getWidth(); i++)
		{
			for (int j = 0; j < environment->getHeight(); j++)
			{	
				cell = environment->getMapData(i, j);
				
				if (std::find(P.begin(), P.end(), cell) == P.end()) //on verifie que le sommet n'est pas dans P
				{
					if (d[cell] < PlusCourteDistance)
					{
						PlusCourteDistance = d[cell];
						a = cell;		//on ajoute la cellule à l'ensemble P car elle est parcourue
					}
				}
			}
		}

		if (a != NULL)
		{
			P.push_back(a);
			std::vector<CellData*> Voisins;


			
					if (d[cell + cell->getX] != environment->getWidth + 1) //adjacent droit
					{
						Voisins.push_back(cell + cell->getX);
					}

					if (d[cell - cell->getX] != -1)	//adjacent gauche
					{
						Voisins.push_back(cell - cell->getX);
					}

					if (d[cell + cell->getY] != environment->getHeight + 1)	//adjacent bas
					{
						Voisins.push_back(cell + cell->getY);
					}

					if (d[cell - cell->getY] != environment->getHeight + 1)	//adjacent haut
					{
						Voisins.push_back(cell - cell->getY);
					}
			
			//comparaison des distances voisines

			std::vector<float> distancesfroma;
			bool sorted = false;

			for (int i = 0; i < Voisins.size; i++)
			{
				
				distancesfroma[i] = sqrt((Voisins[i]->getX - a->getX)*(Voisins[i]->getX - a->getX)+(Voisins[i]->getY - a->getY)*(Voisins[i]->getY - a->getY)); //formule pour calculer une distance entre deux cellules
				
			}

			
		}

	}

	

	
	// TODO : Implémenter un algorithme de recherche de plus court chemin entre startPosition et endPosition
	// qui tient compte de la topologie de l'environnement (environment : case "non marchable"; obstacles, etc...)
	// et des obstacles "dynamique" (les personnages, etc...)
	// Vous représenterez le résultat de votre calcul sous forme d'une liste de position 
	// s'enchainant de la position de départ à la position d'arrivée.

	return path;
}