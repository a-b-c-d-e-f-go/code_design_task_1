#pragma once
#include "Critter.h"
class Destroyer : public Critter
{
public:
	virtual bool Collides(Critter* other) override { return false; } //Ignore collisions itself and continue its current path unhindered.
	virtual char Type() override { return 'd'; } //Count as the destroyer when critters collide with it.
};