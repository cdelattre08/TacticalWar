#pragma once
#include <iostream>
#include "IActionAnimationEventListener.h"
#include <vector>
class BattleActionToAnimation : public IActionAnimationEventListener 
{
	private:
		std::vector<IActionAnimationEventListener*> Listener;
	protected:
		virtual void notifyAnimationFinished(float remainingTime);

public : 
	void addlistener(IActionAnimationEventListener*);
	void removelistener(IActionAnimationEventListener*);
	void start();
	void ellapseTime(float deltatime);
	void update(float deltatime);
};

