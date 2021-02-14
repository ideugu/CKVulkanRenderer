
#include "Precompiled.h"

void Mesh::CalculateBounds()
{
	_SphereBound = Sphere(_Vertices);
	_BoxBound = Box(_Vertices);
}
