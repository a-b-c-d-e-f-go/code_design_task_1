#pragma once
#include "Node.h"

#define forxy loop(x, 0, MAP_WIDTH) { loop(y, 0, MAP_HEIGHT) {
#define _forxy }}

#define n(x, y, c) (*nodes)[x, y]->Add(c);
#define nodes_3x3_add(x, y, c) n(x - 1, y - 1, c) n(x, y - 1, c) n(x + 1, y - 1, c) n(x - 1, y, c) n(x, y, c) n(x + 1, y, c) n(x - 1, y + 1, c) n(x, y + 1, c) n(x + 1, y + 1, c)

struct Map
{
	//Static constant sizes assigned before running the program.
	static const size_t MAP_WIDTH = 16;
	static const size_t MAP_HEIGHT = 16;

	static const size_t SCREEN_WIDTH = 800;
	static const size_t SCREEN_HEIGHT = 450;

	static const size_t NODE_WIDTH = SCREEN_WIDTH / MAP_WIDTH;
	static const size_t NODE_HEIGHT = SCREEN_HEIGHT / MAP_HEIGHT;
	static const size_t NODE_CAPACITY = 50;

	Map();
	~Map();

	bool Add(Critter* _critter);
	void Update(float dt);
	void Draw();
	void Cleanup();

	Node *nodes[MAP_WIDTH][MAP_HEIGHT]{};
};