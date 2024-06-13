#pragma once
#include "AABB.h"
#include "Critter.h"
#include "AL.h"
#include <vector>

struct Node
{
	
	AABB bounds = AABB();
	vector<Critter*> critters{};
	Node();
	Node(AABB _bounds);
	~Node();
	bool Add(Critter* _critter);
	void Collisions();
	void Reset();
	void Draw();
};