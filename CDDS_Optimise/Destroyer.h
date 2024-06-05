#pragma once
#include "Critter.h"
class Destroyer : public Critter
{
public:
	virtual void OnCollide(Critter* other, const int MAX_VELOCITY) override;
	virtual char Type() override { return 'd'; }
};