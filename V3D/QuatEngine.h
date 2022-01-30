#ifndef QUATENGINE_H
#define QUATENGINE_H
#pragma once

#include <string>
#include "Geometrics.h"
#include "Scene.h"
#include "PlaneObject.h"
#include "olcPixelGameEngine.h"

const Vector<float, 3> x_axis(1.0f, 0.0f, 0.0f );
const Vector<float, 3> y_axis(0.0f, 1.0f, 0.0f);
const Vector<float, 3> z_axis(0.0f, 0.0f, 1.0f);

class V3DQEngine : public olc::PixelGameEngine
{
public:
	V3DQEngine();
	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;
private:

	MeshObject o;
	Light l;

	Scene scene;
};

#endif 
