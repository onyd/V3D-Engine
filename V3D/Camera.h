#ifndef CAMERA_H
#define CAMERA_H
#pragma once

#include "Vector.h"
#include "Conversions.h"
#include "Constants.h"
#include "XAble.h"
#include "Plane.h"

class Camera : public Movable, public Directable
{
public:
	Camera() {};
	Camera(Vector<float, 3>& pos, float Zn, float Zf, float fov, float width, float height);

	Matrix<float, 4, 4> getProjectionMatrix() const;
	Matrix<float, 4, 4> getViewMatrix() const;
	Vector<float, 3> getScale() const;

	Plane<float> getEyePlane() const;
	Plane<float> getTopPlane() const;
	Plane<float> getBotPlane() const;
	Plane<float> getLeftPlane() const;
	Plane<float> getRightPlane() const;

	float getHeight() const;
	float getWidth() const;
private:
	void setup(float Zn, float Zf, float fov, float aspect_ratio);

	Matrix<float, 4, 4> _projection_mat;
	float _height;
	float _width;
	Plane<float> _eyePlane;
	Plane<float> _topPlane;
	Plane<float> _botPlane;
	Plane<float> _leftPlane;
	Plane<float> _rightPlane;

};

#endif

