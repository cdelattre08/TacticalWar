#include <PlayerManager.h>
#include <iostream>

using namespace tw;

int main(int argc, char ** argv)
{
	std::vector<tw::Player*> players = PlayerManager::loadPlayers();

	return 0;
}