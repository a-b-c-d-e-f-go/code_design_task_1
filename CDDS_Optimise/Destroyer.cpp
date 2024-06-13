#include "Destroyer.h"

void Destroyer::OnCollide(Critter* other)
{
    other->Destroy(); //Kill any critter touching the destroyer.
}