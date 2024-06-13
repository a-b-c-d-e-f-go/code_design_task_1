#pragma once
#include "Critter.h"
class Destroyer : public Critter
{
public:
	virtual void OnCollide(Critter* other) override;
	virtual char Type() override { return 'd'; }
};