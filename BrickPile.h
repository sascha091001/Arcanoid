#pragma once
#include "Brick.h"
#include <vector>
#include "Puck.h"

class BrickPile
{
public:
	BrickPile();
	~BrickPile();

	void Destroy(Puck p);

	friend class GameTable;
	friend void GameRun();

private:
	Brick *_Brick_Pile;
	int _amount = 50; //Пока фиксированное количество кирпичей
	int _bricks_x = 10;
	int _bricks_y = 5;
};