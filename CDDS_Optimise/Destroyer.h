#pragma once
#include "Critter.h"
class Destroyer : public Critter
{
public:
	virtual void OnCollide(Critter* other) override //Destroy other critter. Do not bounce.
	{
		other->Destroy();
;	}
};