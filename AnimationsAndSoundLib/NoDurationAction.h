#pragma once
#include <iostream>
#include "BattleActionToAnimation.h"
class NoDurationAction : public BattleActionToAnimation
{

public : 

 virtual void update()=0;
	
};

