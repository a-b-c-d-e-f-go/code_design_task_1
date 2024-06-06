#include "QuadTree.h"

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

QuadTree::QuadTree() : children(nullptr), objects(nullptr)
{
	bounds.m_halfSize.x = 1280.0f / 2.0f;
	bounds.m_halfSize.y = 720.0f / 2.0f;
	bounds.m_centre = bounds.m_halfSize;
}
QuadTree::QuadTree(AABB _bounds) : bounds(_bounds), children(nullptr), objects(nullptr)
{

}
QuadTree::~QuadTree()
{
	del_arr(children, 4);
	//del_arr(objects, capacity);
}

bool QuadTree::Add(Critter* _critter)
{
	//if (!bounds.contains(_critter->GetPosition(), _critter->GetHWidth())) //TODO: Make bounds work.
	//{
	//	return false;
	//}

	
	ifv (children) { //If the node has children (is subdivided), attempt to add the critter to them.
		//Find a child node and add the Critter there.
		loop(i, 0, 4) {
			return children[i]->Add(_critter);
		}
	}
	else //Otherwise, add the critter to this node.
	{
		ifn(objects) //If the objects array is empty.
		{
			objects = new Critter * [capacity];
			memset(objects, 0, sizeof(Critter*) * capacity);
		}
		ifn(objects[capacity - 1]) { //If the objects array has at least 1 free space.
			loop(i, 0, capacity) { //Step through the array and look for somewhere to put the Critter.
				ifn(objects[i]) {
					objects[i] = _critter;
					return true;
				}
			}
		}
	}
	return false; //This should never happen
}

void QuadTree::Clear() //Remove all critters from this node its children, and so forth.
{

}

//Split this node into 4 children, and do the same to those children, and so forth, as many times as given by "_recursion".
void QuadTree::Subdivide(int _recursion) //eg. Subdivide(2) splits the node into 16.
{
	children = new QuadTree * [4];

	//Set size of children to half as much in both dimensions.
	Vector2 qSize{ bounds.m_halfSize.x / 2, bounds.m_halfSize.y / 2 };

	//Set position of children to the 4 corners of this node.
	Vector2 qCentre{ bounds.m_centre.x - qSize.x, bounds.m_centre.y - qSize.y };
	children[TOP_LEFT] = new QuadTree(AABB(qCentre, qSize));

	qCentre = Vector2{ bounds.m_centre.x + qSize.x, bounds.m_centre.y - qSize.y };
	children[TOP_RIGHT] = new QuadTree(AABB(qCentre, qSize));

	qCentre = Vector2{ bounds.m_centre.x - qSize.x, bounds.m_centre.y + qSize.y };
	children[BOTTOM_LEFT] = new QuadTree(AABB(qCentre, qSize));

	qCentre = Vector2{ bounds.m_centre.x + qSize.x, bounds.m_centre.y + qSize.y };
	children[BOTTOM_RIGHT] = new QuadTree(AABB(qCentre, qSize));

	//Send objects to children.
	ifv (objects) {
		loop (i, 0, capacity) {
			ifv (objects[i])
			{
				//Find a child node to insert the object into.
				loop (j, 0, 4) {
					if (children[j]->Add(objects[i]))
						break;
				}
				//Remove the object from the objects array for this node.
				objects[i] = nullptr; //Don't delete the object, just reset the pointer. The object still needs to exist in the child node.
			}
		}
		//All of the objects that were stored in this node are now stored in the 
		//child nodes, so delete the objects array.
		delete objects;
		objects = nullptr;
	}

	if (_recursion > 0 && children != nullptr) //If there is recursion, make children subdivide too.
	{
		loop (i, 0, 4) {
			children[i]->Subdivide(_recursion - 1);
		}
	}
}

void QuadTree::Draw()
{
	//Draw the box representing this node's bounds (for debug purposes).
	DrawLine(
		bounds.m_centre.x - bounds.m_halfSize.x, bounds.m_centre.y - bounds.m_halfSize.y,
		bounds.m_centre.x + bounds.m_halfSize.x, bounds.m_centre.y - bounds.m_halfSize.y, RED);
	DrawLine(
		bounds.m_centre.x - bounds.m_halfSize.x, bounds.m_centre.y + bounds.m_halfSize.y - 1,
		bounds.m_centre.x + bounds.m_halfSize.x, bounds.m_centre.y + bounds.m_halfSize.y - 1, RED);
	DrawLine(
		bounds.m_centre.x - bounds.m_halfSize.x + 1, bounds.m_centre.y + bounds.m_halfSize.y,
		bounds.m_centre.x - bounds.m_halfSize.x + 1, bounds.m_centre.y - bounds.m_halfSize.y, RED);
	DrawLine(
		bounds.m_centre.x + bounds.m_halfSize.x, bounds.m_centre.y + bounds.m_halfSize.y,
		bounds.m_centre.x + bounds.m_halfSize.x, bounds.m_centre.y - bounds.m_halfSize.y, RED);

	//Draw all the child nodes, if applicable.
	ifv (children) {
		loop (i, 0, 4) {
			children[i]->Draw();
		}
	}
	//Draw all the objects contained, if applicable.
	ifv (objects) {
		loop (i, 0, capacity) {
			ifv (objects[i])
			{
				objects[i]->Draw();
			}
		}
	}
}