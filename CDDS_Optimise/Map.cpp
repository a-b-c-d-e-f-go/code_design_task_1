#include "Map.h"

Map::Map()
{

}

Map::~Map()
{

}

bool Map::Add(Critter* _critter)
{
	//Coordinates of the critter truncated into unsigned integers from 0-15.
	size_t target_x = (_critter->GetX() / NODE_WIDTH);
	size_t target_y = (_critter->GetY() / NODE_HEIGHT);

	
	nodes_3x3_add(target_x, target_y, _critter);
	return true;
}

void Map::Update(float dt)
{

}

void Map::Draw()
{

}

void Map::Cleanup()
{
	forxy
		delete nodes[x, y];
	_forxy
}