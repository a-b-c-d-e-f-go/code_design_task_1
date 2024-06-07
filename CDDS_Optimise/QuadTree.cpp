#include "QuadTree.h"
#include <iostream>

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

QuadTree::QuadTree() : depth(0), children(nullptr), objects(nullptr)
{
	bounds.m_halfSize.x = 1280.0f / 2.0f;
	bounds.m_halfSize.y = 720.0f / 2.0f;
	bounds.m_centre = bounds.m_halfSize;
}
QuadTree::QuadTree(AABB _bounds, int _depth) : bounds(_bounds), depth(_depth), children(nullptr), objects(nullptr)
{

}
QuadTree::~QuadTree()
{
	del_arr(objects, capacity);
	del_arr(children, 4);
}

bool QuadTree::Add(Critter* _critter)
{
	bool re = false;
	std::cout << "Attempting to add critter " << *_critter << " to node " << bounds << " at depth " << depth << ".\n";
	if (!bounds.contains(_critter->GetPosition(), _critter->GetHWidth())) //Not within bounds.
	{
		std::cout << "FAILED - Outside bounds.\n";
		return false;
	}
	ifv (children) { //If the node has children (is subdivided), attempt to add the critter to them.
		//Find a child node and add the Critter there.
		loop(i, 0, 4) {
			std::cout << "Recursing through children.\n";
			if (children[i]->Add(_critter))
			{
				return true;
				re = true; //Return true at the end.
			}
		}
	}
	else //Otherwise, add the critter to this node.
	{
		ifn(objects) //If the objects array is empty.
		{
			//Allocate memory for a new array.
			objects = new Critter * [capacity];
			memset(objects, 0, sizeof(Critter*) * capacity);
		}
		ifn(objects[capacity - 1]) { //If the objects array has at least 1 free space.
			loop(i, 0, capacity) { //Step through the array and look for somewhere to put the Critter.
				ifn(objects[i]) {
					objects[i] = _critter;
					std::cout << "SUCCESS\n";
					return true;
				}
			}
		}
		else
		{
			Subdivide();
		}
	}
	std::cout << "RETURNED " << re << "\n";
	return re;
}

//Split this node into 4 children, and do the same to those children, and so forth, as many times as given by "_recursion".
void QuadTree::Subdivide(int _recursion) //eg. Subdivide(2) splits the node into 64.
{
	children = new QuadTree * [4];

	//Set size of children to half as much in both dimensions.
	Vector2 qSize{ bounds.m_halfSize.x / 2, bounds.m_halfSize.y / 2 };

	//Set position of children to the 4 corners of this node.
	Vector2 qCentre{ bounds.m_centre.x - qSize.x, bounds.m_centre.y - qSize.y };
	children[TOP_LEFT] = new QuadTree(AABB(qCentre, qSize), depth + 1);
	children[TOP_LEFT]->root = root;

	qCentre = Vector2{ bounds.m_centre.x + qSize.x, bounds.m_centre.y - qSize.y };
	children[TOP_RIGHT] = new QuadTree(AABB(qCentre, qSize), depth + 1);
	children[TOP_RIGHT]->root = root;

	qCentre = Vector2{ bounds.m_centre.x - qSize.x, bounds.m_centre.y + qSize.y };
	children[BOTTOM_LEFT] = new QuadTree(AABB(qCentre, qSize), depth + 1);
	children[BOTTOM_LEFT]->root = root;

	qCentre = Vector2{ bounds.m_centre.x + qSize.x, bounds.m_centre.y + qSize.y };
	children[BOTTOM_RIGHT] = new QuadTree(AABB(qCentre, qSize), depth + 1);
	children[BOTTOM_RIGHT]->root = root;

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

void QuadTree::Update(const float& dt, const int& tick)
{
	const int MAX_VELOCITY = 80; //TODO: REMOVE THIS AND MAKE A GLOBAL VARIABLE OR SMTH
	ifv (objects)
	{
		loop (i, 0, capacity)
		{
			ifv (objects[i])
			{
				if (!objects[i]->IsDead()) //Alive
				{
					if (bounds.contains(objects[i]->GetPosition(), objects[i]->GetHWidth())) //Critter is within this node.
					{
						objects[i]->Update(dt, tick); //Update each critter (dirty flags will be cleared during update).
						//Loop through all other critters in the same node.
						for (int j = 0; j < capacity; j++) {
							ifv(objects[j])
							{
								if (i != j && !objects[i]->IsDirty() && !objects[j]->IsDead()) // note: the other critter (j) could be dirty - that's OK
								{
									//Check every critter against every other critter.
									if (objects[i]->Collides(objects[j]))
									{
										//Break the second loop on collision (still looping through i).
										objects[i]->OnCollide(objects[j], MAX_VELOCITY);
										break;
									}
								}
							}
						}
					}
				}
			}
		}
	}

	ifv(children)
	{
		children[TOP_LEFT]->Update(dt, tick);
		children[TOP_RIGHT]->Update(dt, tick);
		children[BOTTOM_LEFT]->Update(dt, tick);
		children[BOTTOM_RIGHT]->Update(dt, tick);
	}
}

void QuadTree::Draw()
{
	//Draw the box representing this node's bounds (for debug purposes).
	DrawLine(
		(int)bounds.m_centre.x - (int)bounds.m_halfSize.x, (int)bounds.m_centre.y - (int)bounds.m_halfSize.y,
		(int)bounds.m_centre.x + (int)bounds.m_halfSize.x, (int)bounds.m_centre.y - (int)bounds.m_halfSize.y, RED);
	DrawLine(
		(int)bounds.m_centre.x - (int)bounds.m_halfSize.x, (int)bounds.m_centre.y + (int)bounds.m_halfSize.y - 1,
		(int)bounds.m_centre.x + (int)bounds.m_halfSize.x, (int)bounds.m_centre.y + (int)bounds.m_halfSize.y - 1, RED);
	DrawLine(
		(int)bounds.m_centre.x - (int)bounds.m_halfSize.x + 1, (int)bounds.m_centre.y + (int)bounds.m_halfSize.y,
		(int)bounds.m_centre.x - (int)bounds.m_halfSize.x + 1, (int)bounds.m_centre.y - (int)bounds.m_halfSize.y, RED);
	DrawLine(
		(int)bounds.m_centre.x + (int)bounds.m_halfSize.x, (int)bounds.m_centre.y + (int)bounds.m_halfSize.y,
		(int)bounds.m_centre.x + (int)bounds.m_halfSize.x, (int)bounds.m_centre.y - (int)bounds.m_halfSize.y, RED);

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
				Color c = Color{ (unsigned char)(bounds.m_centre.x * 255 * 450), (unsigned char)(bounds.m_centre.y * 255 * 800), 128, 255 };
				objects[i]->Draw(c);
			}
		}
	}
}