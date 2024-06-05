#pragma once
#include "AL.h"
#include "Critter.h"
#include "AABB.h"
#include <vector>

struct Node
{
	
	AABB bounds = AABB();
	vector<Critter*> critters{};
	Node();
	Node(AABB _bounds);
	~Node();
	void Collisions(Critter* _critter);
	void Reset();
	void Draw();
};