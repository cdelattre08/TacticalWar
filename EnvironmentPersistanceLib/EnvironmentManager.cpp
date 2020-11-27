#include "pch.h"
#include "EnvironmentManager.h"
#include <stdlib.h>
#include <iostream>
#include <SFML/System/FileInputStream.hpp>
#include <stdio.h>
#include <vector>
#include <StringUtils.h>
//#include <fstream>
#pragma warning(disable : 4996)
#define TAILLE_MAX 1000 // Tableau de taille 1000


using namespace std;



tw::EnvironmentManager * tw::EnvironmentManager::instance = NULL;

tw::EnvironmentManager * tw::EnvironmentManager::getInstance()
{
	if (instance == NULL)
		instance = new tw::EnvironmentManager();

	return instance;
}

tw::Environment * tw::EnvironmentManager::testEnvironment = NULL;
void tw::EnvironmentManager::createTestEnvironmentIfNotExists()
{
	if (testEnvironment == NULL)
	{
		testEnvironment = new tw::Environment(15, 15, 1);
		testEnvironment->getMapData(1, 1)->setIsWalkable(false);
		testEnvironment->getMapData(2, 2)->setIsObstacle(true);

		testEnvironment->getMapData(13, 13)->setIsWalkable(false);
		testEnvironment->getMapData(12, 12)->setIsObstacle(true);

		testEnvironment->getMapData(0, 0)->setTeamStartPoint(1);
		testEnvironment->getMapData(0, 1)->setTeamStartPoint(1);

		testEnvironment->getMapData(14, 14)->setTeamStartPoint(2);
		testEnvironment->getMapData(13, 14)->setTeamStartPoint(2);
	}
}


tw::Environment * tw::EnvironmentManager::loadEnvironment(int environmentId)
{
	// Equipe éditeur de map : Il faudra charger les données depuis le fichier environmentId.txt
	// situé dans le dossier /assets/map/ et construire une variable de type Environment que vous retournerez.

	/*FILE *fichier;
	fichier = fopen("./assets/map/map.txt", "r");
	if (fichier != NULL)
	{
		for (int i = 0; i < ; i++)
		{
			fscanf(fichier, "%d\n", );
		}
	}
	
	fclose(fichier);
	*/
	
	createTestEnvironmentIfNotExists();
	return testEnvironment;
}

void tw::EnvironmentManager::saveEnvironment(Environment * environment)
{
	// Equipe éditeur de map : Il faudra enregistrer dans un fichier la map
	// passée en paramètre dans le dossier /assets/map/.
	// L'extension du fichier sera .txt
	

	FILE *fichier;
	fichier = fopen("./assets/map/map.txt", "w");
	fprintf(fichier, "%d\n", environment->getId());
	fprintf(fichier, "%d\n", environment->getHeight());
	fprintf(fichier, "%d\n", environment->getWidth());
	for (int i = 0; i < environment->getHeight(); i++) 
	{

		for (int x = 0; x < environment->getWidth(); x++) 
		{
			CellData * cell = environment->getMapData(x, i);
			fprintf(fichier, "%d,%d,%d,%d\n", cell->getX(), cell->getY(),cell->getIsObstacle(), cell->getIsWalkable());
		}

	}
	fclose(fichier);

}