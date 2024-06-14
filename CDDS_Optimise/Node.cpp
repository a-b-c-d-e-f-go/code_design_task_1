#include "Node.h"

Node::Node()
{

}

Node::Node(AABB _bounds) : bounds(_bounds)
{

}

Node::~Node()
{
	critters.clear();
}

void Node::Collisions(Critter* _critter)
{
	for (auto c : critters)
	{
		if (_critter != c && _critter->Collides(c))
		{
			_critter->OnCollide(c);
		}
	}
}

void Node::Reset()
{
	critters.clear();
}

void Node::Draw() //Debug only.
{
	//Draw edges.
	DrawLine(
		(int)bounds.min.x, (int)bounds.min.y,
		(int)bounds.max.x, (int)bounds.min.y, RED);
	DrawLine(
		(int)bounds.min.x, (int)bounds.max.y,
		(int)bounds.max.x, (int)bounds.max.y, RED);
	DrawLine(
		(int)bounds.min.x, (int)bounds.max.y,
		(int)bounds.min.x, (int)bounds.min.y, RED);
	DrawLine(
		(int)bounds.max.x, (int)bounds.max.y,
		(int)bounds.max.x, (int)bounds.min.y, RED);

	//Show critter count.
	if (critters.size() > 0 && critters[0] != nullptr) {
		unsigned char a = (critters.size() * 255 / CRITTER_COUNT);
		Color c = Color{ 255, 0, 0, a};
		DrawRectangle((int)bounds.min.x, (int)bounds.min.y, (int)(bounds.max.x - bounds.min.x), (int)(bounds.max.y - bounds.min.y), c);
	}
}