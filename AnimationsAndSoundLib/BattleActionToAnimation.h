#pragma once
#include <iostream>
#include "IActionAnimationEventListener.h"
#include <vector>

class BattleActionToAnimation
{
	private:
		std::vector<IActionAnimationEventListener*> Listener;
		float elseTime;
	protected:
		void notifyAnimationFinished(float remainingTime);

public : 
	void addlistener(IActionAnimationEventListener*);
	void removelistener(IActionAnimationEventListener*);
	void start();
	void elapseTime(float deltatime);
	void update(float deltatime);
};

