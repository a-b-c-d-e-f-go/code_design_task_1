#include "Node.h"
#include <iostream>

Node::Node()
{

}

Node::Node(AABB _bounds) : bounds(_bounds)
{

}

Node::~Node()
{
}

void Node::Collisions(Critter* _critter)
{
	for (vector<Critter*>::iterator iter = critters.begin(); iter < critters.end(); iter++)
	{
		cout << "checc";
		if (_critter->Collides(critters[0]))
		{
			_critter->OnCollide(critters[0]);
		}
	}
	critters.push_back(_critter);
}

void Node::Reset()
{
	critters.clear();
}

void Node::Draw()
{
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

	//Draw all the critters contained, if applicable.
	if (critters.size() > 0 && critters[0] != nullptr) {
		DrawRectangle((int)bounds.min.x, (int)bounds.min.y, (int)(bounds.max.x - bounds.min.x), (int)(bounds.max.y - bounds.min.y), Color{ 255, 0, 0, 30 });
		/*loop(i, 0, NODE_CAPACITY) {
			ifv(critters[i])
			{
				Color c = Color{ (unsigned char)(bounds.min.x / 800 * 255), (unsigned char)(bounds.min.y / 450 * 255), 255, 255 };
				critters[i]->Draw(c);
			}
		}*/
	}
}