#include "AABB.h"
#include "Critter.h"
#pragma once

class QuadTree
{
public:
	enum Quarters {
		TOP_LEFT = 0,
		TOP_RIGHT,
		BOTTOM_LEFT,
		BOTTOM_RIGHT
	};

	QuadTree();
	QuadTree(AABB _bounds, int _depth = 0);
	~QuadTree();

	
	bool Add(Critter* _critter);
	void Subdivide(int _recursion = 0);
	void Update(const float& dt, const int& tick);
	void Draw();

private:
	static const int capacity = 5;
	int depth;
	AABB bounds;
	QuadTree** children; //Pointer to an array.
	Critter** objects; //Pointer to an array.
	QuadTree* root = this;
};