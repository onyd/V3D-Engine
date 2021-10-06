#ifndef LIGHTS_H
#define LIGHTS_H
#pragma once

#include "Vector.h"
#include "XAble.h"

class Light : public Directable
{
public:
	Light();
	Light(Vector<float, 3>& dir);

private:
};

#endif // !LIGHTS
