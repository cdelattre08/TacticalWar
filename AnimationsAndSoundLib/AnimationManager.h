#pragma once
#include <stdio.h>
#include "BattleActionToAnimation.h"
#include <vector>
class AnimationManager : public IActionAnimationEventListener 
{
	private :
		std::vector<BattleActionToAnimation*> animationtime;
	public:
		virtual void update(float datatime);
		virtual void onAnimationFinished(float remainingTime);
		virtual void clear();
};

