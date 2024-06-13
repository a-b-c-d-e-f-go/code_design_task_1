#include "Node.h"

Node::Node()
{

}

Node::Node(AABB _bounds) : bounds(_bounds)
{

}

Node::~Node()
{
}

bool Node::Add(Critter* _critter)
{
	critters.push_back(_critter);
	return false;
}

void Node::Collisions()
{
	for (auto& i : critters) {
		for (auto& j : critters) {
			if (i != j && !i->IsDirty() && !j->IsDead()) // note: the other critter (j) could be dirty - that's OK
			{
				//Check every critter against every other critter.
				if (i->Collides(j))
				{
					//Break the second loop on collision (still looping through i).
					i->OnCollide(j, MAX_VELOCITY);
					break;
				}
			}
		}
	}
	critters.clear();
}

void Node::Reset()
{
	
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