#ifndef LIGHTS_CPP
#define LIGHTS_CPP

#include "Lights.h"

Light::Light()
	: Directable()
{
}

Light::Light(Vector<float, 3>& dir)
	: Directable()
{
}

#endif // !LIGHTS_CPP
