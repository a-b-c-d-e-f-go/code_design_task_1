#pragma once
#include "AABB.h"
#include "Critter.h"

#define ifv(ptr) if (ptr != nullptr) //If valid (for pointers).
#define ifn(ptr) if (ptr == nullptr) //If null (for pointers).
#define loop(var, start, end) for (int var = start; var < end; var++) //For loop preset.

//Delete array (for cleanup).
#define del_arr(arr, size)					\
ifv (arr) {									\
	loop (i, 0, size) { 					\
		ifv (arr[i]) {						\
			delete arr[i];					\
		}									\
	}										\
	delete arr;								\
	arr = nullptr;							\
}

struct Node
{
	AABB bounds = AABB();
	Critter** critters;
	Node();
	Node(AABB _bounds);
	~Node();
	void Add(Critter* _critter);
};