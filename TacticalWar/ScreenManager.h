#pragma once

#include "Screen.h"
namespace tw
{
	class ScreenManager
	{
	private:
		static ScreenManager * instance;
		ScreenManager() { currentScreen = NULL; }

		Screen * currentScreen;

	public:

		static ScreenManager * getInstance();

		Screen * getCurrentScreen()
		{
			return currentScreen;
		}

		void setCurrentScreen(Screen * screen)
		{
			currentScreen = screen;
		}
	};
}
