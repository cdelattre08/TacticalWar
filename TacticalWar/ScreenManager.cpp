#include "ScreenManager.h"

using namespace tw;

ScreenManager * ScreenManager::instance = NULL;

ScreenManager * ScreenManager::getInstance()
{
	if (instance == NULL)
		instance = new ScreenManager();

	return instance;
}
