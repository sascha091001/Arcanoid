#pragma once

class Puck
{
public:
	Puck();
	~Puck();

	friend class BrickPile;
private:
	int _size_x;
	int _size_y;

	int _pos_x;
	int _pos_y;
};

