#include "Destroyer.h"

void Destroyer::OnCollide(IEntity* other, const int MAX_VELOCITY)
{
    other->Destroy(); //Kill any critter touching the destroyer.
}