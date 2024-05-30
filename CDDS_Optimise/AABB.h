//Based on https://github.com/AcademyOfInteractiveEntertainment/AIEYear1Samples
//Uses min/max xy values instead of centre and half width/half height because its more convenient for drawing and collision checks.

#pragma once
#include "raymath.h"
#include <iostream>

using namespace std;

struct AABB
{
	AABB() : min(Vector2{0, 0}), max(Vector2{ 0, 0 }) {}
	AABB(Vector2 _min, Vector2 _max) : min(_min), max(_max) {}

	bool contains(Vector2 point, float leeway = 0.0f) const
	{
		if (point.x - leeway < min.x || //If the point's x is < the box's left
			point.x + leeway > max.x || //or the point's x is > the box's right
			point.y - leeway < min.y || //or the point's y is < the box's bottom
			point.y + leeway > max.y)   //or the point's y is > the box's top
		{
			return false; //Then they can't possibly be intersecting.
		}
		return true; //If all the checks are false, then they are.
	}

	bool intersects(AABB other) const
	{
		if (max.x < other.min.x ||		//If this box's right edge is < other box's left
			min.x > other.max.x ||		//or this box's left edge is > other box's right
			max.y < other.min.y ||		//or this box's top edge is < other box's bottom
			min.y > other.max.y)		//or this box's bottom edge is  > other box's top
		{
			return false; //Then they can't possibly be intersecting.
		}
		return true; //If all the checks are false, then they are.
	}

	Vector2 min;
	Vector2 max;

	friend ostream& operator<<(ostream& os, const AABB& b) //Print as (x1,y1,x2,y2)
	{
		os << "(" << b.min.x << "," << b.min.y << "," << b.max.x << "," << b.max.y << ")";
		return os;
	};
};