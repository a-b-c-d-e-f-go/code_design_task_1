#pragma once
#include "Node.h"

struct Map
{
	

	Map();
	~Map();

	bool Add(Critter* _critter);
	void Collisions();
	void Reset();
	void Draw();
	void Cleanup();

	Node* nodes[MAP_COLUMNS][MAP_ROWS];
};