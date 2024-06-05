#include "Map.h"

Map::Map()
{
	forxy
		nodes[x][y] = new Node(AABB(Vector2{ x * (float)NODE_WIDTH, y * (float)NODE_HEIGHT }, Vector2{ (x + 1) * (float)NODE_WIDTH, (y + 1) * (float)NODE_HEIGHT }));
	_forxy
}

Map::~Map()
{
	forxy
		delete nodes[x][y];
	_forxy
}

void Map::Collisions(Critter* _critter)
{
	ifv(_critter)
	{
		//Coordinates of the critter truncated into unsigned integers from 0-15.
		size_t tx = (size_t)(_critter->GetX() / (float)NODE_WIDTH);
		size_t ty = (size_t)(_critter->GetY() / (float)NODE_HEIGHT);

		Check(_critter, tx - 1, ty - 1);
		Check(_critter, tx, ty - 1);
		Check(_critter, tx + 1, ty - 1);

		Check(_critter, tx - 1, ty);
		Check(_critter, tx, ty);
		Check(_critter, tx + 1, ty);

		Check(_critter, tx - 1, ty + 1);
		Check(_critter, tx, ty + 1);
		Check(_critter, tx + 1, ty + 1);

		if (tx < MAP_COLUMNS && ty < MAP_ROWS)
		{
			nodes[tx][ty]->critters.push_back(_critter);
		}
	}
}

void Map::Check(Critter* _critter, size_t _x, size_t _y)
{
	if (_x < MAP_COLUMNS && _y < MAP_ROWS)
	{
		nodes[_x][_y]->Collisions(_critter);
	}
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