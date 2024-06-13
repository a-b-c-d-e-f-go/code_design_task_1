#include "Map.h"
#include <iostream>

Map::Map()
{
	forxy
		nodes[x][y] = new Node(AABB(Vector2{ x * (float)NODE_WIDTH, y * (float)NODE_HEIGHT }, Vector2{ (x + 1) * (float)NODE_WIDTH, (y + 1) * (float)NODE_HEIGHT }));
	_forxy
}

Map::~Map()
{

}

bool Map::Add(Critter* _critter)
{
	ifv(_critter)
	{
		//Coordinates of the critter truncated into unsigned integers from 0-15.
		size_t target_x = (size_t)_critter->GetX() / NODE_WIDTH;
		size_t target_y = (size_t)_critter->GetY() / NODE_HEIGHT;
		//nodes_3x3_add(target_x, target_y, _critter);
		if(target_x < MAP_COLUMNS && target_y < MAP_ROWS)
		{
			return nodes[target_x][target_y]->Add(_critter);
		}
	}
	return false;
}

void Map::Collisions()
{
	forxy
		nodes[x][y]->Collisions();
	_forxy
}

void Map::Reset()
{
	forxy
		nodes[x][y]->Reset();
	_forxy;
}

void Map::Draw()
{
	forxy
		nodes[x][y]->Draw();
	_forxy
}

void Map::Cleanup()
{
	forxy
		delete nodes[x][y];
	_forxy
}