#include <PlayerManager.h>
#include <iostream>

using namespace tw;

int main(int argc, char ** argv)
{
	std::vector<tw::Player*> players = PlayerManager::loadPlayers();

	std::cout << "Liste des joueurs : \n" << std::endl;
	for (int i = 0; i < players.size(); i++)
	{
		std::cout << "Login : " << players[i]->getPseudo() << std::endl;
		std::cout << "Password : " << players[i]->getPassword() << std::endl;
		std::cout << "Team : " << players[i]->getTeamNumber() << std::endl << std::endl;
	}

	return 0;
}