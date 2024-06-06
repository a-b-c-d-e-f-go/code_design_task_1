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
	QuadTree(AABB _bounds);
	~QuadTree();

	
	bool Add(Critter* _critter);
	void Clear();
	void Subdivide(int _recursion = 0);

	//void Update(float deltaTime);
	void Draw();

private:
	static const int capacity = 51;
	AABB bounds;
	QuadTree** children; //Pointer to an array.
	Critter** objects; //Pointer to an array.
};