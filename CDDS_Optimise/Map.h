#pragma once
#include "Node.h"

struct Map
{
	

	Map();
	~Map();

	void Collisions(Critter* _critter);
	void Check(Critter* _critter, size_t _x, size_t _y);
	void Reset();
	void Draw();

	Node* nodes[MAP_COLUMNS][MAP_ROWS];
};