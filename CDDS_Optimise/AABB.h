//https://github.com/AcademyOfInteractiveEntertainment/AIEYear1Samples

#pragma once
#include "raymath.h"
#include <iostream>

using namespace std;

class AABB
{
public:
	AABB() {}
	AABB(Vector2 centre, Vector2 halfSize) : m_centre(centre), m_halfSize(halfSize) {}

	bool contains(Vector2 point, float leeway = 0.0f) const
	{
		if (point.x - leeway < m_centre.x + m_halfSize.x &&
			point.x + leeway > m_centre.x - m_halfSize.x &&
			point.y  - leeway < m_centre.y + m_halfSize.y &&
			point.y + leeway > m_centre.y - m_halfSize.y)
			return true;
		return false;
	}

	bool intersects(AABB other) const
	{
		if (m_centre.x + m_halfSize.x < other.m_centre.x - other.m_halfSize.x ||		// if this box's right edge is < other box's left
			m_centre.x - m_halfSize.x > other.m_centre.x + other.m_halfSize.x ||		// or this box's left edge is > other box's right
			m_centre.y + m_halfSize.y < other.m_centre.y - other.m_halfSize.y ||		// or this box's top edge is < other box's bottom
			m_centre.y - m_halfSize.y > other.m_centre.y + other.m_halfSize.y)			// or this box's bottom edge is  > other box's top
			return false;																// then they can't possibly be intersecting
		return true;
	}

	inline float x1() const { return m_centre.x - m_halfSize.x; }
	inline float y1() const { return m_centre.y - m_halfSize.y; }
	inline float x2() const { return m_centre.x + m_halfSize.x; }
	inline float y2() const { return m_centre.y + m_halfSize.y; }

	Vector2 m_centre;
	Vector2 m_halfSize;

	friend ostream& operator<<(ostream& os, const AABB& b)
	{
		os << "(" << b.x1() << "," << b.y1() << "," << b.x2() << "," << b.y2() << ")";
		return os;
	};
};