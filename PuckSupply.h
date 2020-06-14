#pragma once
#include <vector>
#include "Puck.h"
class PuckSupply
{
public:
	PuckSupply(int HP);
	Puck getPuck();
	~PuckSupply();
	friend class GameTable;
	friend void GameRun();
private:
	Puck *_Puck_arr;
	int _cnt;
};

