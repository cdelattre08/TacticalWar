#include "pch.h"
#include "PlayerManager.h"
#include <fstream>
#include <string>
#include <iostream>
#include <deque>
using namespace std;

tw::Match * tw::PlayerManager::testMatch = NULL;

std::vector<tw::Player*> tw::PlayerManager::loadPlayers()
{
	int index = 1;
	std::vector<tw::Player*> result;

	// Vous devrez remplacer les données de test par des 
	// données chargées depuis un fichier.
	ifstream fichierTeam("../assets/equipe.txt");

	if (fichierTeam)
	{
		cout << "Ouverture reussi\n" << endl;
		string dataFile;

		fichierTeam >> dataFile;

		vector<std::string> result = StringUtils::explode(dataFile, '/');

		cout << "Liste des joueurs : \n" << endl;
		
		for (int i = 0; i < result.size(); i++)
		{
			cout << "joueur" << index << " : " << result[i] << endl;
			index++;
		}

		vector<std::string> result1 = StringUtils::explode(dataFile, ',');

		for (int i = 0; i < result1.size(); i++)
		{
			/* Enlever les '/' pour le déocupage clean.
			if (result1[i] != '/')
			{
				cout << result1[i] << endl;	
			}*/
			cout << result1[i] << endl;
		}
	}
	else {
		cout << "Pas reussi\n" << endl;
	}

	result.push_back(new Player("J1", "P1", 1));
	result.push_back(new Player("J2", "P2", 1));
	result.push_back(new Player("J3", "P3", 2));
	result.push_back(new Player("J4", "P4", 2));

	return result;
}

tw::Match * tw::PlayerManager::getCurrentOrNextMatchForPlayer(tw::Player * p)
{
	createTestMatchIfNotExists();

	// TODO : Rechercher le match courant ou le prochain pour le joueur p 
	// et le retourner. Si aucun match à venir, retourner NULL.

	if (testMatch->getStatus() != FINISHED)
	{
		return testMatch;
	}

	return NULL;
}

std::vector<tw::Match*> tw::PlayerManager::getCurrentlyPlayingMatchs()
{
	std::vector<tw::Match*> result;

	createTestMatchIfNotExists();

	if (testMatch->getStatus() == MatchStatus::STARTED)
	{
		result.push_back(testMatch);
	}

	return result;
}
